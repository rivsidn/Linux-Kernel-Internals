* `arch/x86/kernel/ftrace.c` 文件
* 
* 先看 `kernel/trace/ftrace.c`
* 再看 `kernel/trace/trace_events_filter.c`
* 







```c
int register_ftrace_function() {
    __register_ftrace_function();
    ftrace_startup(0);
}

```



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

* 内核中 `nmi` 会嵌套执行么？

* `cpu_relax()` 实现？

* 通过 `bochs` `qemu` 虚拟机追踪内核调试机制

* `arch/x86/kernel/ftrace.c` 中的汇编代码

* 

* `mm/macess.c` 函数实现？

* `framer` 信息？内核中的宏定义

* `stop_machine.c` 文件用处？

* `function_trace_init()` 函数中同时调用了

  * `tracing_start_cmdline_trace()` 
    * 这个函数是什么时候生效的？如何查看现象
    * 是否可以通过设置 `set_ftrace_filter` 过滤掉
  * `tracind_start_function_trace()`
    * 这个函数是如何生效的？

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





