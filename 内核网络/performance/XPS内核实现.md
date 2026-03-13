
基于 `4.19.190` 内核.

## 基本原理





## 参数配置





## 附录

### TODO

- 为什么会发生CPU切换



### 配置接口

```
==== XPS Configuration

XPS is only available if the kconfig symbol CONFIG_XPS is enabled (on by
default for SMP). The functionality remains disabled until explicitly
configured. To enable XPS, the bitmap of CPUs/receive-queues that may
use a transmit queue is configured using the sysfs file entry:

For selection based on CPUs map(基于CPU映射):
/sys/class/net/<dev>/queues/tx-<n>/xps_cpus

For selection based on receive-queues map(基于接收队列映射):
/sys/class/net/<dev>/queues/tx-<n>/xps_rxqs

```

### AI

#### 1

```
● 太好了！现在我可以给你完整的解释了。

  XPS 如何影响 qdisc 处理

  关键流程

  发送数据包
      ↓
  netdev_pick_tx()  ← (net/core/dev.c:3712) 选择 TX
  队列
      ↓
  get_xps_queue()   ← (net/core/dev.c:3628) XPS
  查询映射表
      ↓
  【确定 queue_index】
      ↓
  netdev_get_tx_queue(dev, queue_index) ←
  获取对应的队列
      ↓
  【这个队列有自己的 qdisc】
      ↓
  qdisc->enqueue()  ← 入队到这个 qdisc
      ↓
  __netif_schedule(qdisc) ← 调度这个 qdisc

  XPS 的核心机制（net/core/dev.c:3628-3668）

  static int get_xps_queue(struct net_device *dev,
  struct net_device *sb_dev,
                         struct sk_buff *skb)
  {
      struct xps_dev_maps *dev_maps;

      // 1. 获取 XPS CPU 映射表
      dev_maps = rcu_dereference(sb_dev->xps_cpus_map);
      if (dev_maps) {
          unsigned int tci = skb->sender_cpu - 1;  //
  获取发送 CPU

          // 2. 根据 CPU 查找对应的队列
          queue_index = __get_xps_queue_idx(dev, skb,
  dev_maps, tci);
      }

      return queue_index;
  }

  关键点：skb->sender_cpu 记录了发送数据包的 CPU
  编号（net/core/dev.c:3656）

  队列选择的完整逻辑（net/core/dev.c:3686-3709）

  static u16 __netdev_pick_tx(struct net_device *dev,
  struct sk_buff *skb,
                            struct net_device *sb_dev)
  {
      int queue_index = sk_tx_queue_get(sk);  // 1.
  尝试从 socket 缓存获取

      if (queue_index < 0 || skb->ooo_okay ||
          queue_index >= dev->real_num_tx_queues) {

          // 2. 优先使用 XPS 选择队列
          int new_index = get_xps_queue(dev, sb_dev,
  skb);

          if (new_index < 0)
              // 3. XPS 失败，使用哈希算法
              new_index = skb_tx_hash(dev, sb_dev,
  skb);

          // 4. 缓存队列选择结果到 socket
          sk_tx_queue_set(sk, new_index);

          queue_index = new_index;
      }

      return queue_index;
  }

  XPS 配置如何生效

  当你设置 XPS：

  # 假设有 4 个 TX 队列（tx-0, tx-1, tx-2, tx-3）
  # 将 tx-0 绑定到 CPU 0（二进制 0001 = 1）
  echo 1 > /sys/class/net/eth0/queues/tx-0/xps_cpus

  # 将 tx-1 绑定到 CPU 1（二进制 0010 = 2）
  echo 2 > /sys/class/net/eth0/queues/tx-1/xps_cpus

  # 将 tx-2 绑定到 CPU 2（二进制 0100 = 4）
  echo 4 > /sys/class/net/eth0/queues/tx-2/xps_cpus

  # 将 tx-3 绑定到 CPU 3（二进制 1000 = 8）
  echo 8 > /sys/class/net/eth0/queues/tx-3/xps_cpus

  内核会建立映射表：xps_cpus_map（net/core/dev.c:3654）

  CPU 0 → tx-0 → qdisc_0
  CPU 1 → tx-1 → qdisc_1
  CPU 2 → tx-2 → qdisc_2
  CPU 3 → tx-3 → qdisc_3

  XPS 如何解决你的跨 CPU 问题

  没有 XPS 的情况：

  CPU 0: 发送数据包
    ↓
    选择队列（可能是任意队列，比如 tx-1）
    ↓
    qdisc_1->enqueue()
    ↓
    __netif_schedule(qdisc_1)
    ↓
    放入 CPU 0 的 softnet_data
    ↓
    【但 tx-1 可能由 CPU 1 的软中断处理】← 跨 CPU！

  配置 XPS 之后：

  CPU 0: 发送数据包
    ↓
    get_xps_queue() 查询：CPU 0 → tx-0
    ↓
    qdisc_0->enqueue()
    ↓
    __netif_schedule(qdisc_0)
    ↓
    放入 CPU 0 的 softnet_data
    ↓
    【tx-0 专门由 CPU 0 处理】← 同一个 CPU！

  完整的数据流

  应用进程（CPU 0）
      ↓
  系统调用 send()
      ↓
  TCP/IP 协议栈
      ↓
  dev_queue_xmit()
      ↓
  netdev_pick_tx() ← 【XPS 在这里起作用】
      |
      +-- get_xps_queue()  ← 查询：CPU 0
  应该用哪个队列？
      |       ↓
      |   返回 queue_index = 0（tx-0）
      |
      ↓
  netdev_get_tx_queue(dev, 0) ← 获取 tx-0
      ↓
  qdisc_0 = txq->qdisc ← 每个 TX 队列有自己的 qdisc
      ↓
  qdisc_0->enqueue(skb) ← 入队到 qdisc_0
      ↓
  __qdisc_run(qdisc_0) ← 尝试立即发送
      ↓
  如果队列满或超配额：
      __netif_schedule(qdisc_0)
          ↓
      this_cpu_ptr(&softnet_data) ← CPU 0 的队列
          ↓
      raise_softirq_irqoff(NET_TX_SOFTIRQ) ← 触发 CPU 0
   的软中断
          ↓
  【软中断在 CPU 0 执行】
      net_tx_action()
          ↓
      qdisc_0->dequeue() ← 从 qdisc_0 出队
          ↓
      sch_direct_xmit() ← 发送到网卡驱动

  关键总结

  XPS 的作用就是建立 CPU → TX 队列的绑定关系：

  1. 入队时：根据当前 CPU 选择对应的 TX 队列（和
  qdisc）
  2. 调度时：将 qdisc 放入当前 CPU 的 softnet_data
  3. 出队时：软中断在同一个 CPU 执行，处理同一个 qdisc

  这样就实现了同一个 CPU 完成入队和出队，避免跨 CPU！

```

#### 2

```
  答案：不是一定依附于 netdev_queue                    
                                                       
  qdisc 分为两种：                                     
                                                       
  1. 叶子 qdisc（Leaf Qdisc）                          
                                            
  必须依附于 netdev_queue，因为它们要真正发送数据包。  

  例如：
  - pfifo_fast（默认 qdisc）
  - pfifo、bfifo
  - tbf（令牌桶）
  - fq_codel

  从代码看（net/sched/sch_mq.c:93-103）：

  for (ntx = 0; ntx < dev->num_tx_queues; ntx++) {
      dev_queue = netdev_get_tx_queue(dev, ntx);  //
  获取 TX 队列
      qdisc = qdisc_create_dflt(dev_queue, ...);   //
  创建 qdisc 并绑定
      priv->qdiscs[ntx] = qdisc;
      qdisc->flags |= TCQ_F_ONETXQUEUE |
  TCQ_F_NOPARENT;  // 标记为叶子节点
  }

  2. 分类 qdisc（Classful Qdisc）

  不一定依附于 netdev_queue，它们只是调度器/容器。

  例如：
  - mq（multiqueue，多队列调度器）
  - mqprio（multiqueue priority）
  - htb（hierarchical token bucket，层次令牌桶）
  - prio（优先级调度器）
  - cbq（class based queueing）

  qdisc 的层次结构

  以多队列网卡为例：

  网卡设备（eth0）
      ↓
  root qdisc: mq ← 【不绑定具体 netdev_queue】
      ├── 子 qdisc_0 → netdev_queue[0] ← 【绑定 TX 队列
   0】
      ├── 子 qdisc_1 → netdev_queue[1] ← 【绑定 TX 队列
   1】
      ├── 子 qdisc_2 → netdev_queue[2] ← 【绑定 TX 队列
   2】
      └── 子 qdisc_3 → netdev_queue[3] ← 【绑定 TX 队列
   3】

  或者更复杂的 HTB 例子：

  网卡设备（eth0）
      ↓
  root qdisc: htb ← 【不绑定具体 netdev_queue，只有
  dev_queue 指针】
      ├── class 1:1 (总带宽)
      │   ├── class 1:10 (高优先级) → 叶子 qdisc
  (pfifo)
      │   ├── class 1:20 (普通流量) → 叶子 qdisc
  (pfifo)
      │   └── class 1:30 (低优先级) → 叶子 qdisc
  (pfifo)
      └── 这些叶子 qdisc 共享同一个 dev_queue

  从数据结构看

  include/net/sch_generic.h:89：

  struct Qdisc {
      int (*enqueue)(...);
      struct sk_buff *(*dequeue)(...);

      u32 parent;  ← 【父 qdisc 的
  handle，如果没有父则为 TC_H_ROOT】

      struct netdev_queue *dev_queue;  ← 【可能为 NULL
  或指向具体队列】

      // ...
  };

  关键标志位

  从代码看（include/net/sch_generic.h:76-80）：

  #define TCQ_F_NOPARENT   0x40  // 没有父
  qdisc（根或叶子）
  #define TCQ_F_MQROOT     0x08  // 多队列的根 qdisc
  #define TCQ_F_ONETXQUEUE 0x10  // 只对应一个 TX
  队列（叶子 qdisc）

  mq 的特殊性（net/sched/sch_mq.c:2）：

  /*
   * net/sched/sch_mq.c    Classful multiqueue dummy
  scheduler
   *                       ^^^^^^^^^^^^^^^^^^^^^^^^^
  注意：dummy！
   */

  mq 本身是"虚拟的"，不处理数据包：
  - 它的 enqueue 和 dequeue 都是空操作
  - 真正的工作由它的子 qdisc 完成
  - 它自己不绑定 netdev_queue

  实际检查

  你可以用命令查看：

  # 查看 qdisc 结构
  tc qdisc show dev eth0

  # 可能输出：
  # qdisc mq 0: root             ← mq 是
  root，没有绑定具体队列
  # qdisc pfifo_fast 0: parent :1  ← 子
  qdisc，绑定到队列

  总结

  只有真正需要发送数据包的叶子 qdisc 必须依附于
  netdev_queue。

  分类 qdisc（mq、htb、prio
  等）只是调度器，不直接发送数据包，所以不一定绑定
  netdev_queue。

  这就像：
  - 叶子 qdisc = 机场登机口（必须有实体位置）
  - 分类 qdisc = 候机大厅管理系统（虚拟的，只负责调度）

```

