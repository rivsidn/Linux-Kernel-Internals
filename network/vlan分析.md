

`vlan` 功能和`br_vlan` 功能是分开的，先梳理`vlan` 功能。



搭个实际的环境，梳理一下，当前`vlan` 部分代码的用处？

报文是否是带有`tag`？

什么时候带`tag`？什么时候不带？



## 重要函数

|                  |        |
| ---------------- | ------ |
| skb_vlan_untag() | ？？？ |
|                  |        |











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

