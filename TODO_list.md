## 进行中

* `tracepoint` `trace event` 实现？
* 





## 内存问题

* 内核内存检测 `KASAN`
  * `KASAN` 实现

* 内核内存泄漏问题 `kmemleak`



## 调试

* 通过`kdb` 或者 `ftrace` 获取函数变量，获取函数返回值
* 通过`kdb` 跟踪函数执行分支，查看局部变量
* `livepatch` 功能



## 文档整理

* 如何读代码
* 



## 其他

* 

* `call_rcu_sched()` 实现

* `static_key_slow_inc()` 4.4 内核怎么理解？`jump_label` 用处

* `vmlinux.lds.h` 实现？

* 常用的二进制工具

* `double_lock_balance()` 函数的用法？

* `put_cpu_var()` `get_cpu_var()`用法？

* `CONFIG_DYNAMIC_DEBUG`使用，`netdev_dbg()`

* 内核模块加载流程？

* `CONFIG_DEBUG_INFO`下边内容

* 内核代码中的测试用例是如何写的？

* 如何理解`/proc/meminfo` 显示的内容

* `print_stack_trace()` `save_stack_trace()`函数实现？

* 内核代码是在哪里设置的 `skb->transport_header` ？

* 关中断之后是否可能引起调度？不可屏蔽中断是否会引起调度

  当前暂时认为，不可屏蔽中断不会引起调度

* 内核`mutex_lock()`实现

* 内核`spin_lock()` 实现

* `rcu` 内核调试

* `CONFIG_TRACE_IRQFLAGS` 设置

* `kallsyms.c` 实现

* `task_pid_nr` 和 `task_pid_nr_ns` 之间什么关系？有什么差异？

* `dump_stack` 的实现

* `local_irq_save()`  `local_irq_restore()` 实现？

* 如何解决内核踩内存问题，如何定位

* `__init` `__exit` 标识符使用？

* 

* `GDB` 使用

* `NMI` 中断处理

* 

* `core_initcalll()` 如何使用？何时才能 `printk`？

* `module_exit()` 中的函数是在什么时候执行的？

* `modules_init()` 当成模块加载的时候是如何执行的？

* 2.6 内核报文如何做NAT

* 2.6 内核的`socket` 处理

* RPS/RFS 实现

* `ptype` proc 文件系统使用，对比`uptime` 实现

* 4.4.155  proc 文件系统使用

* 文件系统中几个重要的结构体

* `arp` 邻居信息处理

* 2.4 内核中所有中断的初始化，分别是做什么用的

* `INIT_DELAYED_WORK_DEFERRABLE()` 是如何使用的？

* `cond_resched()` 函数的作用？精确到内核调度算法

* `kmemdup()` 函数实现？

* `lock_class_key` 这个结构体的用法？

* `macvlan.c` 这个驱动的用处？

* `skb_push()`、`skb_pull()`  这两个函数的使用，`skb`数据结构

* `skb` 中的 `len` `data_len` `skb_headlen()` `skb_pagelen()`  这几个分别是做什么用的？

* `skb_header_pointer()` 这个函数的用处？

* 内核中bitmap 的使用

* `hlist_for_each_entry_rcu()` 使用？

* `get_unique_tuple()` 中 `pr_debug()` 输出？

* 

* `kmalloc()` 标识位使用？

* 

* __force 这个关键字是做什么用的？

* 

* `__builtin_constant_p()` 的使用，起什么作用？内建函数整理

* `2.6` 内核的进程调度



## 进程调度

* 等待队列
* 

## 数据结构

* list, hlist, list_rcu, hlist_rcu
* `lockdep` 代码实现？数据结构，算法，宏定义



## 并发编程

* 内存屏障？("": : : "memory") 实现理解？
* 编译器乱序？CPU乱序？CPU缓存？分别对代码执行的影响，以及应该用哪种同步机制
* 内存屏障，`ACCESS_ONCE()` 
* `read_seqbegin()` 中的 `smp_rmb()` 和 `rcu_dereference()` 中的 `ACCESS_ONCE()` 如何结合起来理解？
* 



## 调试环境



## 代码检测工具

* `sparse` 使用？

