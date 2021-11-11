

| 内核控制宏              | Kconfig文件       | 作用                                 |
| ----------------------- | ----------------- | ------------------------------------ |
| CONFIG_LOCKDEP          | lib/Kconfig.debug |                                      |
| CONFIG_DEBUG_LOCKDEP    | lib/Kconfig.debug | 调试lockdep功能                      |
| CONFIG_DEBUG_LOCK_ALLOC | lib/Kconfig.debug | 检测已经获取的锁是是否被不正常的释放 |
| CONFIG_PROVE_LOCKING    | lib/Kconfig.debug | 保证加锁的数学正确性                 |
| CONFIG_LOCK_STAT        | lib/Kconfig.debug | 加锁统计                             |
|                         |                   |                                      |
|                         |                   |                                      |





| lock_usage_bit            |                   | 二进制 | 十进制 |
| ------------------------- | ----------------- | ------ | ------ |
| LOCKDEP_STATE(HARDIRQ)    | USED_IN           | 0000   | 0      |
|                           | USED_IN_READ      | 0001   | 1      |
|                           | ENABLE_STATE      | 0010   | 2      |
|                           | ENABLE_STATE_READ | 0011   | 3      |
| LOCKDEP_STATE(SOFTIRQ)    | USED_IN           | 0100   | 4      |
|                           | USED_IN_READ      | 0101   | 5      |
|                           | ENABLE_STATE      | 0110   | 6      |
|                           | ENABLE_STATE_READ | 0111   | 7      |
| LOCKDEP_STATE(RECLAIM_FS) | USED_IN           | 1000   | 8      |
|                           | USED_IN_READ      | 1001   | 9      |
|                           | ENABLE_STATE      | 1010   | 10     |
|                           | ENABLE_STATE_READ | 1011   | 11     |
| USED                      |                   | 1100   | 12     |





## 重要的结构体

* `lockdep_map{}`

  外部锁跟`lockdep` 模块之间交互的结构体，建立与 `held_lock{}` 与 `lock_class{}`之间联系。

  **与锁类之间的映射关系还需要分析**

* `held_lock{}`

  存在于进程结构体`task_struct{}` 中的结构体数组，表示当前进程获取到的锁，会随着进程运行，锁的释放、获取，该结构体数组中的有效数据量会增减，`task_struct{}`中的另一个变量`depth` 表示该结构体数组有效数据的数量。

* `lock_chain{}`

  缓存的作用，`held_lock{}` 之间的映射关系会随着程序运行不断变化，此时出现的序列之前可能存在过，加入是这种情况，则不需要进行检测。

* `lock_class{}`

  锁类，用于检测锁之间是否有环，或者是否中断是否可能导致优先级反转。

* `lock_list{}`

  通过该结构体，建立锁类与类之间的依赖关系。



## 死锁类型



## TODO

* `lockdep_map{}`与锁类之间的映射关系？分析锁实现的代码的时候进一步分析

  `lockdep_map` 和`lock_class` 之间是一一映射的么？

* `lock_chain()` 这个结构体是做什么用的？

  缓存作用 `held_lock{}` 是会随着程序运行不断变换的，可能会出出现这样的情况，相同的锁序列在之前运行的过程中出现过，那么此时就不需要进行检测。

* `init_utsname()`实现？

* 还是没理解 `lockdep_recursion` 这个值的用处？

* `2.6.25`内核中使能之后，为什么 `rcu_dereference()` 不在 `rcu_read_lock()` 之中会报异常

  注释掉 `skb_dst()` 中的`WARN_ON` 宏。

* 死锁检测可以检测到所有有可能的死锁么？能检测到的条件是什么？该功能有什么优势

  * 某进程调用一个自旋锁，中断打断其他进程调用该自旋锁，此时是可能引起死锁的，这中情况能检测到么？

    应该是能检测到的，该锁出现的两种`state` 是互斥的。

* `held_lock{}` 这个结构体的第一个变量是做什么用的？

* `get_usage_chars()` 函数中宏的实现？

* `locking-selftest.c` 代码梳理，如何写测试用例？

* 

* 



