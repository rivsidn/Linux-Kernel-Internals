# linux-kernel


## 整理图格式

- 梳理数据结构关系
- 梳理函数调用关系
- 梳理函数执行流程
- 梳理锁之间互斥
- 状态机转化图


## TODO

- `0.98` 精读0.98 内核网络协议代码
- linux内核是否支持优先级反转机制，如何实现的?
- 以[链接](https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=4f11ada10d0ad3fd53e2bd67806351de63a4f9c3)为例分析内核commit的组成部分
- 分析内核中的读写锁
- 梳理内核RCU实现
- 梳理内核NETFILTER实现
- 梳理内核会话实现
- 梳理内核NAT实现
- 分析内核邮件列表



- CONFIG_SYSTEM_TRUSTED_KEYS 这个配置的功能.
- 如何能够精确的描述定时器中的算法？
  - 添加
  - 执行
- 内核中的工作队列机制
  - 没有完全梳理清楚
- 内核中的定时器
- epoll 内核实现
- Linux 内核的许可证认证，这两种有什么区别
  ```c
  EXPORT_SYMBOL_GPL(destroy_workqueue);
  EXPORT_SYMBOL(schedule_work);
  ```
  是如何限制的内核模块访问
- 内核中获取cpu号的函数之间区别
  - smp...
  - raw_smp..
  - get_cpu


