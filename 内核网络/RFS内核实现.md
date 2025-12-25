## V2.6.35

### 前期准备

```bash
# 获取内核提交
git log --pretty=format:"%h%x09%ad%x09%an%x09%s" --date=short  net/core/dev.c | grep rfs
# 生成分支
git checkout -b RFS-annotation fec5e652e58f~1
# 检查patch
git apply --check 0001-rfs-Receive-Flow-Steering.patch
# 应用patch
git apply 0001-rfs-Receive-Flow-Steering.patch
```



```
#相关提交
fec5e652e58f	2010-04-16	Tom Herbert	rfs: Receive Flow Steering
```



### 基本思想

`RFS` 是在`RPS` 基础上实现的。

```
      get_rps_cpu
           |
           |
     Y     v
+---------RFS
|          |
|          | N
|          |
|          v
|         RPS
|          |
|          |
|          v
+------> return
```

如上所示，函数`get_rps_cpu()` 中 `RFS` 处理在`RPS` 之前，如果通过`RFS`处理流程找到了匹配的`CPU`，后续不会调用`RPS`调用获取对应`CPU`。

`RFS`对应的`CPU`是通过函数`inet_rps_record_flow()` 存储的，该函数在`inet_sendmsg()`、`inet_sendpage()`、`inet_recvmsg()`中调用，用于存储流对应的`CPU`。



### 核心算法

`last_qtail`、`input_queue_head` 两个变量作用？

`last_qtail`将报文放到队列中时更新：

```c
/* static int enqueue_to_backlog(struct sk_buff *skb, int cpu, unsigned int *qtail) */
#ifdef CONFIG_RPS
			*qtail = queue->input_queue_head +
			    queue->input_pkt_queue.qlen;
#endif
```

`input_queue_head` 将报文取出时递增：

```c

static inline void incr_input_queue_head(struct softnet_data *queue)
{
#ifdef CONFIG_RPS
	queue->input_queue_head++;
#endif
}
```

每次将报文放入缓冲队列中， 会存储当前队列的队尾，在`get_rps_cpu()`中判断：

```c
		if (unlikely(tcpu != next_cpu) &&
		    (tcpu == RPS_NO_CPU || !cpu_online(tcpu) ||
		     ((int)(per_cpu(softnet_data, tcpu).input_queue_head - rflow->last_qtail)) >= 0)) {
			tcpu = rflow->cpu = next_cpu;
			if (tcpu != RPS_NO_CPU)
				rflow->last_qtail = per_cpu(softnet_data, tcpu).input_queue_head;
}
```

当`intpu_queue_head`大于`last_qtail` 表示此时之前放进去的报文已经处理。

为了防止乱序，只有之前的报文处理了，才会改变`CPU`。

```
                           last_qtail
                                |
                                |
                                v
        n  n+1  n+2  n+3  ...  n+x
        ^
        | <------- len ---------->
        |
input_queue_head
```

如上所示，`input_queue_head`递增，当超过`last_qtail`时，表示该报文已经被处理。



## 附录

### TODO

* 内核`patch`合入过程，`RPS`是何时合入的？

