基于`linux-2.6.35.6` 内核。



以为 `trace/events/skb.h` 中 `TRACE_EVENT(kfree_skb, ...)` 为例子分析代码实现。



| 涉及文件                     |      |
| ---------------------------- | ---- |
| include/trace/events/skb.h   |      |
|                              |      |
| include/linux/tracepoint.h   |      |
|                              |      |
| include/trace/define_trace.h |      |
| include/trace/ftrace.h       |      |
|                              |      |
| net/core/net-traces.c        |      |
|                              |      |
|                              |      |



`TRACE_EVENT(kfree_skb, ...)`  在 `include/trace/events/skb.h` 中定义，包含该头文件的时候，按照是否定义了`CREATE_TRACE_POINTS` 可以分成两种情况。

| 文件                    | 是否定义`CREATE_TRACE_POINTS` |
| ----------------------- | ----------------------------- |
| `net/core/skbuff.c`     | 否                            |
| `net/core/net-traces.c` | 是                            |



## 否

没定义`CREATE_TRACE_POINTS`的时候，`include/trace/events/skb.h` 中的

```c
#include <trace/define_trace.h>
```

中没其作用，此时`TRACE_EVENT()` 会直接用`include/trace/tracepoint.h` 中的宏定义展开成`DECLARE_TRACE()`，按照头文件中定义，最终会通过`__DECLARE_TRACE()`展开生成如下，一个引用的外部符号表，和四个函数。

```c
extern struct tracepoint __tracepoint_##name;
static inline void trace_##name() {}
static inline int register_trace_##name() {}
static inline int unregister_trace_##name() {}
static inline void check_trace_callback_type_##name() {}
```

所以，可以在`net/core/skbuff.c` 中调用

```c
trace_kfree_skb();
```



## 是

这个地方如何理解？

其中的宏定义是如何依次展开的？





## TODO

* `__DO_TRACE()` 中为什么要调用 `rcu_read_lock_sched_notrace()` 函数？

  这个一个宏定义，如果调用正常的函数，可能会跟 `trace` 部分功能的宏定义产生耦合。

* 

