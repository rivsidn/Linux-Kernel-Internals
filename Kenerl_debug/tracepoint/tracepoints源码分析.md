以`net_dev_xmit` 实现分析`tracepoint` 实现．



## 头文件

```c
//include/trace/events/net.h　中定义

TRACE_EVENT(net_dev_xmit,							//事件名

        TP_PROTO(struct sk_buff *skb,				//原型
                 int rc,
                 struct net_device *dev,
                 unsigned int skb_len),

        TP_ARGS(skb, rc, dev, skb_len),				//参数名

		//省略...
);
```



`net.h` 会在源文件中展开，当没定义`CREATE_TRACE_POINTS`时会生成：

```c
extern struct tracepoint __tracepoint_net_dev_xmit;
//实际调用的函数
static void trace_net_dev_xmit(struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len);
static void trace_net_dev_xmit_rcuidle(struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len);
//注册钩子函数ＡＰＩ
static int register_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data);
static int register_trace_prio_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data, int prio);
//注销钩子函数ＡＰＩ
static int unregister_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data);
static void check_trace_callback_type_net_dev_xmit(void (*cb)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len));
//tracepoint是否使能ＡＰＩ
static bool trace_net_dev_xmit_enabled(void);
```



倘若定义了`CREATE_TRACE_POINTS` 此时会生成`__tracepoint_net_dev_xmit` 定义等其他信息，具体参见`net-trace.i` 文件．



## 原生钩子函数注册

```c
//event使能接口
__ftrace_event_enable_disable()
{
    //注册接口
    ret = call->class->reg(call, TRACE_REG_REGISTER, file);
}
```

根据`net-trace.i` 文件中查找, 最终发现将`net-trace.i` 文件中的 `trace_event_raw_event_net_dev_xmit()` 注册到了处理函数中.



## 注册自己的钩子函数

```c
#inlucde <trace/event/net.h>

//调用register_trace_subsys_eventname() 即可
```

**需要将通过EXPORT_TRACEPOINT_SYMBOL_GPL() 将自己添加的符号表导出才能在模块中引用.**



## 附录

### 内核生成预处理文件

```bash
make net/core/dev.i
make net/core/net-traces.i
```

