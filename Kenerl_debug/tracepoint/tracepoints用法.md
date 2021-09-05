`tracepoints` 使用分两部分：

1. 头文件中定义
2. C文件中使用



## 定义

头文件定义设计三个宏：

1. `TRACE_EVENT`
2. `DECLARE_EVENT_CLASS`
3. `DEFINE_EVENT`

其中，`TRACE_EVENT` 直接定义了一个事件；

`DECLARE_EVENT_CLASS` 定义了一个事件处理模板，在`DEFINE_EVENT` 中可以直接引用这个模板。

详细使用可以参见源码。



## 使用

直接在代码中调用即可。

```c
int netif_rx(struct sk_buff *skb)
{
    trace_netif_rx_entry(skb);
    return netif_rx_internal(skb);
}
```



## 挂载钩子函数

是否可以挂载自己的处理函数？

如何挂载自己的钩子函数？





## 附录

### TODO

1. `event` 是根据什么在`/sys/kernel/tracing/available_events`中分类的？

   同一类的`event`是在目录`include/trace/events/`下同一个头文件中定义的。

   头文件的开始定义了`TRACE_SYSTEM`。

2. 是如何在头文件中定义的？

   

3. 







