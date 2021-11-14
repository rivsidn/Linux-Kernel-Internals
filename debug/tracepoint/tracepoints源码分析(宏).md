基于`linux-2.6.35.6` 内核。



主要分析 `trace/events/skb.h` 。



| 涉及文件                     |      |
| ---------------------------- | ---- |
| include/trace/events/skb.h   |      |
| include/trace/define_trace.h |      |
|                              |      |
|                              |      |
| include/linux/tracepoint.h   |      |
|                              |      |
|                              |      |
| net/core/net-traces.c        |      |
|                              |      |
|                              |      |





## TODO

* `__DO_TRACE()` 中为什么要调用 `rcu_read_lock_sched_notrace()` 函数？

  这个一个宏定义，如果调用正常的函数，可能会跟 `trace` 部分功能的宏定义产生耦合。

* 

