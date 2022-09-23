## V2.6.35

### 前期准备

```bash
# 查找
git log --pretty=format:"%h%x09%ad%x09%an%x09%s" --date=short  net/core/dev.c > ~/tmp.log
for id in $(cat ~/tmp.log | grep 'rps' | cut -d '     ' -f 1); do git format-patch -1 ${id} -o /home/yuchao/linux-kernel/linux-rps/; done;
# 创建分支
git checkout -b RPS-annotation 0a9627f2649a~1
git branch -m RPS-annotation v2.6.35-RPS-annotation
```

### 功能描述

```
                      +------->  netif_rx ------------+     +-> get_rps_cpu
                      |                               |     |
      +---------------+                               +-----+
      |               |                               |     |
      |               +------->  netif_receive_skb----+     +-> enqueue_to_backlog
net_rx_action
      |
      |
      |
      +---------------> net_rps_action
```

处理流程如图所示，主要分两步：

1. 报文上送协议栈之前，调用`get_rps_cpu()` 获取报文上送的CPU，然后通过`enqueue_to_backlog()`将报文放到队列中。
2. 函数调用`net_rps_action()`通知对端`CPU`处理过来的报文



