

## 重要函数

| 函数名               | 解释                                   |
| -------------------- | -------------------------------------- |
| br_vlan_init()       | 创建桥时候初始化桥设备vlan相关结构体   |
| br_vlan_add()        | 桥添加vlan                             |
| nbp_vlan_add()       | 创建桥口的时候，添加桥口vlan相关结构体 |
| nbp_vlan_add()       | 桥口添加vlan                           |
| __vlan_add()         | 公共的vlan添加函数                     |
|                      |                                        |
| br_vlan_should_use() | 这个函数的用处？？                     |
|                      |                                        |
| br_handle_vlan()     |                                        |
| br_allowed_ingress() |                                        |
| br_allowed_egress()  |                                        |
|                      |                                        |
| __br_deliver()       | 本机向外发包                           |
| __br_forward()       | 桥报文转发                             |
| br_pass_frame_up()   | 报文上本机                             |
|                      |                                        |











## 重要数据结构

### vlan_info

### vlan_group







* skb_vlan_untag()
* 桥`vlan` 相关数据结构是如何初始化的？
* 桥口下的数据结构组织？
* `__br_vlan_filter_toggle()` 函数？
* 收包入口函数在哪里？
* `2.6` 内核vlan 是如何工作的？





## TODO

### 功能流程

* vlan_dev.c
* `vlan_gro_receive()`、`vlan_gro_complete()` 作用？
* 设备up的时候，添加设备到vlan 0 中的作用？
* `vlan_gro_receive()`、`vlan_gro_complete()` 作用？
* `vlan` 设备如何收发包、包文过滤
* `gvrp` 与 `garp` 之间工作流程
* `netif_keep_dst()` 作用？

### API

* skb_push()
* skb_pull()
* dev_add_offload()
* 



## 附录

