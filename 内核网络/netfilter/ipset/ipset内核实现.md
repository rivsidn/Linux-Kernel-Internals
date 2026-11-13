
## 核心文件

```makefile
ip_set-y := ip_set_core.o ip_set_getport.o pfxlen.o
```

| 文件             | 主要职责               |
|------------------|------------------------|
| ip_set_core.c    | 集合框架；用户接口     |
| ip_set_getport.c | 从数据包提取协议和端口 |
| pfxlen.c         | 辅助计算网段           |


## 核心结构体

网络命名空间
  └─ ip_set_net.ip_set_list[id] → ip_set（一个具体集合）
                                  ├─ type → ip_set_type（类型定义）
                                  ├─ variant → ip_set_type_variant（操作函数）
                                  └─ data → bitmap/hash/list 的私有数据

 结构体                                                                                                                                    作用
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 struct ip_set_net (ip_set_core.c:32)                                                                                                      每个网络命名空间的集合表。ip_set_list 按 ID
                                                                                                                                           找到 ip_set，ip_set_max 限制集合数量。
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────  ─────────────────────────────────────────────
 struct ip_set (/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.19.190/include/linux/netfilter/ipset/ip_set.h:230)                 一个集合实例，保存名称、锁、引用计数、IPv4/
                                                                                                                                           IPv6 类型、元素数量、超时和扩展布局。data
                                                                                                                                           指向该类型真正存放元素的数据结构。
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────  ─────────────────────────────────────────────
 struct ip_set_type (/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.19.190/include/linux/netfilter/ipset/ip_set.h:195)            集合类型的定义，例如 hash:ip。描述名称、维
                                                                                                                                           度、支持的地址族与版本，并提供创建函数和
                                                                                                                                           Netlink 属性校验策略。一个类型可以创建多个
                                                                                                                                           ip_set 实例。
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────  ─────────────────────────────────────────────
 struct ip_set_type_variant (/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.19.190/include/linux/netfilter/ipset/ip_set.h:149)    具体操作的函数表。kadt 处理数据包触发的查
                                                                                                                                           找/增删，uadt 处理用户态命令；还包含底层增
                                                                                                                                           删查、扩容、清空、列出和销毁等回调。
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────  ─────────────────────────────────────────────
 struct ip_set_adt_opt (/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.19.190/include/linux/netfilter/ipset/ip_set.h:139)         数据包路径上一次 Add/Delete/Test 操作的参
                                                                                                                                           数：地址族、匹配维度、源/目的方向、命令标志
                                                                                                                                           及扩展信息。
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────  ─────────────────────────────────────────────
 struct ip_set_ext (/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.19.190/include/linux/netfilter/ipset/ip_set.h:116)             元素操作时传递的附加信息，如超时、包/字节计
                                                                                                                                           数、注释和 skb 信息。集合实例里的
                                                                                                                                           extensions、dsize、offset[] 决定这些信息如
                                                                                                                                           何存储在元素旁边。

ip_set->data 的实际形态取决于类型：bitmap:ip 指向含位图和 IP 范围的 struct bitmap_ip (ip_set_bitmap_ip.c:42)；hash 类型指向含哈希表、容量和定时器的类型私有结构，其表由 htable 和
hbucket 组成；list:set 则指向含其他集合引用链表的 struct list_set (ip_set_list_set.c:44)。

一次数据包查询大致是：集合 ID → ip_set_net 找到 ip_set → 调用 variant->kadt() → 在 data 中查找元素。ip_set_core.c (ip_set_core.c:567)


› ip_set 这个结构体是怎么加到 ip_set_net 中的？


• 我沿 CREATE 命令的调用链看一下分配、初始化、扩容和写入 ip_set_list 的具体位置。

• Explored
  └ Read ip_set_core.c, ip_set_hash_ip.c

• ip_set 不是嵌入到 ip_set_net 结构体里的，而是单独分配，然后把它的指针放进 ip_set_net.ip_set_list 数组。

  创建流程在 ip_set_create() (ip_set_core.c:881) 中：

  1. ip_set_net_init() 先为每个网络命名空间分配一个空的 ip_set_list 指针数组。ip_set_core.c (ip_set_core.c:2062)
  2. 用户态发来 IPSET_CMD_CREATE，核心代码用 ip_set_pernet(net) 取得当前命名空间的 ip_set_net，再用 kzalloc() 分配一个 struct ip_set。
  3. 根据请求的类型找到 ip_set_type，调用 set->type->create() 初始化类型私有数据，即 set->data 和对应的操作函数表。ip_set_core.c (ip_set_core.c:933)
  4. find_free_id() 检查名称冲突并找到数组中的空位；数组满时会扩容。最后执行关键赋值：ip_set(inst, index) = set;。ip_set_core.c (ip_set_core.c:980)

  所以最终关系是 ip_set_net.ip_set_list[index] → struct ip_set。这个 index 就是后续内核数据包路径查找集合时使用的 ID。

