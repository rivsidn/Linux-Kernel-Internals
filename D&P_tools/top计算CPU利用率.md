

## CPU占用时间

| 时间                      | 缩写 | 解释                                                         |
| ------------------------- | ---- | ------------------------------------------------------------ |
| 用户时间(User time)       | us   | 表示CPU执行用户进程的时间，包括nices 时间                    |
| 系统时间(System time)     | sy   | 表示CPU内核态运行的时间，包括IRQ 和 softirq 时间             |
| Nice时间(Nice time)       | ni   | 系统调整进程优先级花费的时间                                 |
| 等待时间(Waiting time)    | id   | CPU等待I/O操作完成花费的时间。<br />花费时间高说明存在I/O瓶颈 |
| 空闲时间(Idle time)       | wa   | 处于空闲期，等待进程运行                                     |
| 硬中断时间(Hard Irq time) | hi   | 处理硬中断花费的时间                                         |
| 软中断时间(Soft Irq time) | si   | 处理软件中断花费的时间                                       |
| 丢失时间(Steal time)      | st   | 被强制等待(involuntary wait) 虚拟CPU的时间，<br />此时`hypervisor`在另一个虚拟处理器服务 |
|                           |      |                                                              |



这些数据都是通过`/proc/stat` 获取的。



## TODO

内核时间计算，为什么当调度繁忙的时候，计算的`idle`值会比实际值低。



## 参考资料

* [聊聊top命令中的CPU使用率](https://juejin.cn/post/6968357584558358565)