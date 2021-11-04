| 内核控制宏              | Kconfig文件       | 作用                                 |
| ----------------------- | ----------------- | ------------------------------------ |
| CONFIG_LOCKDEP          | lib/Kconfig.debug |                                      |
| CONFIG_DEBUG_LOCKDEP    | lib/Kconfig.debug | 调试lockdep功能                      |
| CONFIG_DEBUG_LOCK_ALLOC | lib/Kconfig.debug | 检测已经获取的锁是是否被不正常的释放 |
| CONFIG_PROVE_LOCKING    | lib/Kconfig.debug | 保证加锁的数学正确性                 |
| CONFIG_LOCK_STAT        | lib/Kconfig.debug | 加锁统计                             |
|                         |                   |                                      |
|                         |                   |                                      |





* 使能之后，为什么 `rcu_dereference()` 不在 `rcu_read_lock()` 之中会报异常

  注释掉 `skb_dst()` 中的`WARN_ON` 宏。

* 死锁检测可以检测到所有有可能的死锁么？能检测到的条件是什么？该功能有什么优势

  * 某进程调用一个自旋锁，中断打断其他进程调用该自旋锁，此时是可能引起死锁的，这中情况能检测到么？

    应该是能检测到的，该锁出现的两种`state` 是互斥的。

  * 

* `held_lock{}` 这个结构体的第一个变量是做什么用的？



