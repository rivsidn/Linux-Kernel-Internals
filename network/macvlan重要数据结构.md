## macvlan_port

| 结构体成员                                             | 解释                               |
| ------------------------------------------------------ | ---------------------------------- |
| struct net_device *dev;                                | 对应实际的物理设备                 |
| struct hlist_head vlan_hash[MACVLAN_HASH_SIZE];        | mac地址hash表，快速查询macvlan设备 |
| struct list_head vlans;                                | macvlan设备列表                    |
| struct rcu_head rcu;                                   |                                    |
| struct sk_buff_head bc_queue;                          |                                    |
| struct work_struct bc_work;                            |                                    |
| bool passthru;                                         |                                    |
| int count;                                             |                                    |
| struct hlist_head vlan_source_hash[MACVLAN_HASH_SIZE]; |                                    |







## TODO

* list_first_or_null_rcu()
* 