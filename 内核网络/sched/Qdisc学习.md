

rtnl_register(PF_UNSPEC, RTM_NEWQDISC, tc_modify_qdisc, ...) (net/sched/sch_api.c:2173)

所以这条命令的内核处理函数是：

tc_modify_qdisc() (net/sched/sch_api.c:1412)

命令参数会编码为 Netlink 属性，大致对应：

 命令部分     Netlink 字段
━━━━━━━━━━━  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 dev eth0     tcmsg.tcm_ifindex = eth0 的 ifindex
───────────  ────────────────────────────────────────────────────
 root         tcmsg.tcm_parent = TC_H_ROOT
───────────  ────────────────────────────────────────────────────
 pfifo        TCA_KIND = "pfifo"
───────────  ────────────────────────────────────────────────────
 limit 100    TCA_OPTIONS = struct tc_fifo_qopt { .limit = 100 }
───────────  ────────────────────────────────────────────────────
 add          RTM_NEWQDISC，并带 `NLM_F_CREATE

内核处理路径：

tc qdisc add dev eth0 root pfifo limit 100
  -> NETLINK_ROUTE: RTM_NEWQDISC
  -> tc_modify_qdisc()
  -> qdisc_create()
  -> qdisc_lookup_ops(TCA_KIND="pfifo")
  -> 找到 pfifo_qdisc_ops
  -> pfifo_qdisc_ops.init() = fifo_init()
  -> fifo_init() 从 TCA_OPTIONS 读取 limit = 100
  -> qdisc_graft()
  -> 挂到 eth0 的 root Qdisc 位置

关键位置：

• tc_modify_qdisc(): create_n_graft (net/sched/sch_api.c:1548)：创建并挂接 Qdisc。
• qdisc_create() (net/sched/sch_api.c:1067)：根据 TCA_KIND 查找 pfifo 的 Qdisc_ops，并调用 .init。
• qdisc_graft() (net/sched/sch_api.c:937)：把新建 Qdisc 替换进设备 root 位置；设备已启用时，会先停用再重新启用发送路径。
• pfifo_qdisc_ops (net/sched/sch_fifo.c:104)：注册 pfifo 的 enqueue、dequeue、init 等回调。
• fifo_init() (net/sched/sch_fifo.c:58)：从 struct tc_fifo_qopt 取出 limit=100，赋给 sch->limit。
• pfifo_enqueue() (net/sched/sch_fifo.c:31)：队列中不足 100 个报文则入队，否则丢弃新报文。



补充一点：对于多 TX 队列网卡，root pfifo 的 graft 分支会遍历所有 dev->num_tx_queues，将这个 root Qdisc 关联到各 TX 队列，而不是只处理 dev->_tx[0]，
见 qdisc_graft() (net/sched/sch_api.c:967)。

