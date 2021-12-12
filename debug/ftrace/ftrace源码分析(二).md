主要分析 **event filter** 功能实现。

```bash
# 例子摘自 Documentation/trace/events.txt
$ cd /debug/tracing/events/sched/sched_signal_send
$ echo "((sig >= 10 && sig < 15) || sig == 17) && comm != bash" > filter
```



实现的功能有：

* 获取函数参数名，参数类型
* 解析表达式
* `event` 调用之前需要先匹配 `filter`





##  TODO

* `tracepoint` 和 `trace event` 之间还是没联系起来







