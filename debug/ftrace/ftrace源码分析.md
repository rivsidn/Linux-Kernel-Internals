* 弄明白`trace_functions.c` 这个文件的用处？





* 切换 `tracer` 时候执行的操作？

  ```c
  //以 ftrace 为例
  
  //切换到该tracer 时候调用该函数
  static int function_trace_init()
  {
      tracing_start_cmdline_record();
      tracing_start_function_trace();
  }
  
  
  
  tracing_sched_wakeup_trace() 中最后两行的作用？运行的时候
  
  
  ```

  

* 







## TODO

* `register_ftrace_command()` 这个函数的作用？

* `ftrace_preempt_disable()` 理解这个函数

* `ftrace()` 函数是在什么时候调用的？

* `trace_events_filter.c` 文件实现？

  * `filter_check_discard()` 实现

* `dump_trace()` 实现？ `stacktrace.c` 实现

* `ring_buffer` 实现梳理？

* 结构体作用

  * trace_array{}

* options 是如何添加的，为什么nop 的两个选项没有添加上

* 如何与`traefs` 交互？

* `ring_buffer.c` 的实现？

* `trace_boot.c` 做什么用的？

* `debugfs` 文件系统实现？

* `trace_branch.c` 功能？与其他的 `tracer` 之间的关系？

* `ftrace_event.h` 文件作用？

* `trace_events.c` 实现？

* `kmemcheck_bitfield_begin()` 使用？

* 下边这些宏的用处

  ```c
  #define RB_FLAG_NORMAL	0UL
  #define RB_FLAG_HEAD	1UL
  #define RB_FLAG_UPDATE	2UL
  
  #define RB_FLAG_MASK	3UL
  
  #define RB_PAGE_MOVED	4UL
  ```

* 





