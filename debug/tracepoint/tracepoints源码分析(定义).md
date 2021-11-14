基于 `linux-4.4.155` 内核。

`tracepoint` 用法在内核代码文件 `Documentation/trace/tracepoints.txt` 中.

以`net_dev_xmit` 实现分析内核`tracepoint` 实现．

| 文件                       | 作用                                    |
| -------------------------- | --------------------------------------- |
| include/trace/events/net.h | 通过宏定义了`net_dev_xmit` 实现相关代码 |
| net/core/dev.c             | `trace_net_dev_xmit` 具体使用           |
| net/core/net-traces.c      | `net_dev_xmit` 定义                     |



## 代码片段

```c
/* include/trace/events/net.h */
TRACE_EVENT(net_dev_xmit,						//tracepoint 名称
        TP_PROTO(struct sk_buff *skb,			//函数原型
                 int rc,
                 struct net_device *dev,
                 unsigned int skb_len),
        TP_ARGS(skb, rc, dev, skb_len),			//函数参数名称

        //函数中执行的具体动作相关部分代码
        TP_STRUCT__entry(
                __field(        void *,         skbaddr         )
                __field(        unsigned int,   len             )
                __field(        int,            rc              )
                __string(       name,           dev->name       )
        ),

        TP_fast_assign(
                __entry->skbaddr = skb;
                __entry->len = skb_len;
                __entry->rc = rc;
                __assign_str(name, dev->name);
        ),

        TP_printk("dev=%s skbaddr=%p len=%u rc=%d",
                __get_str(name), __entry->skbaddr, __entry->len, __entry->rc)
);
```


```c
/* net/core/net-traces.c */
#define CREATE_TRACE_POINTS										//定义了这个宏的时候会定义变量,申请存储空间
#include <trace/events/net.h>
```

定义了 `CREATE_TRACE_POINTS`  的时候引用会创建变量, 所以当有多个引用了该头文件的原文件存在时,只能有一个源文件中定义`CREATE_TRACE_POINTS`．

```c
/* net/core/dev.c */
#include <trace/events/net.h>

static int xmit_one(struct sk_buff *skb, struct net_device *dev,
                    struct netdev_queue *txq, bool more)
{
        unsigned int len; 
        int rc;

        if (!list_empty(&ptype_all) || !list_empty(&dev->ptype_all))
                dev_queue_xmit_nit(skb, dev);

        len = skb->len;
        trace_net_dev_start_xmit(skb, dev);                                                                                                            
        rc = netdev_start_xmit(skb, dev, txq, more);
        trace_net_dev_xmit(skb, rc, dev, len);					//插入到代码执行流程中

        return rc;
}
```

当没定义 `CREATE_TRACE_POINTS` 时, `net.h` 中有关`tracepoint`的宏定义会正常展开, 引用外部变量. 



## 函数接口

由于直接追踪宏定义的展开比较复杂, 可以直接生成预处理文件, 查看预处理文件的内容.

```bash
# 生成预处理文件
make net/core/dev.i
make net/core/net-traces.i
# 查找net_dev_xmit 有关内容
grep 'net_dev_xmit' net/core/dev.i > dev_xmit.i
grep 'net_dev_xmit' net/core/net-traces.i > net-traces_xmit.i
```



查看dev_xmit.i 中内容, 将我们比较感兴趣的整理如下:

```c
extern struct tracepoint __tracepoint_net_dev_xmit;
//调用的函数
static void trace_net_dev_xmit(struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len)
//注册钩子函数ＡＰＩ
static int register_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data)
//注销钩子函数ＡＰＩ
static int unregister_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data)
//tracepoint是否使能ＡＰＩ
static bool trace_net_dev_xmit_enabled(void)
```

如上所示, 在`dev.c` 中,引用了外部变量 `__tracepoint_net_dev_xmit`,该变量在`net-traces.c` 中定义.

内核默认会给我们注册一个钩子函数, 用于实现`event` 相关功能(基于`tracepoint`实现的 `event`功能稍后展示)。

此时可以通过`register_trace_net_dev_xmit()` 将我们自己的钩子函数注册到这个`tracepoint` 的钩子函数中。



## 附录

### 内核生成预处理文件

```bash
make net/core/dev.i
make net/core/net-traces.i
```

