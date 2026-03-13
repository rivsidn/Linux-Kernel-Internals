* 分析`tracepoint` 中的宏定义
* 分析`trace_event_filter.c` 中的代码实现

* 这段如何理解

  ```
  The advantage of using the trace_<tracepoint>_enabled() is that it uses
  the static_key of the tracepoint to allow the if statement to be implemented
  with jump labels and avoid conditional branches.
  ```


