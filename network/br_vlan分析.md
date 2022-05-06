`vlan` 设备就是一个虚拟设备，实现的流程和其他的虚拟设备实现类型基本一致。

* 报文上来之后，收包，设备`skb->dev` 为`vlan`设备，继续递交协议栈处理
* 报文发送时候，会走到`vlan`设备对应的`xmit()` 函数，在该函数中将报文发送到具体的物理设备

`vlan` 设备设置具体的`vlan id` 之后，只能接收对应`vlan tag`的包文(只能根据`vlan tag`查找虚拟设备)，发送出来的报文也必须是带`vlan tag`的。



`br_vlan` 是一个功能拓展，实现桥的`vlan` 过滤功能，使得当前的桥设备处理类似于交换机。

* 接收到不带`vlan tag`的报文，根据端口的`pvid`处理
* 接收到带`vlan tag` 的报文按照对应的`vlan tag`处理
* 报文发送出去时，可以按照配置，决定是否发送`vlan tag`

由于该功能是一个拓展，所以主要是通过函数接口实现的，将函数接口嵌入到桥的报文处理流程中。



## 函数接口

| 函数接口             | 解释                                                         |
| -------------------- | ------------------------------------------------------------ |
| br_allowed_ingress() | 收包过滤                                                     |
| br_allowed_egress()  | 发包过滤                                                     |
| br_handle_vlan()     | 报文`vlan`处理。<br />发送不带`tag`的报文是在该函数内部处理的。 |



## 重要结构体

| 结构体                  | 说明                                                         |
| ----------------------- | ------------------------------------------------------------ |
| net_bridge_vlan_group{} | 桥、桥端口设备都一个该结构体                                 |
| net_bridge_vlan{}       | `vlan`表项，桥、桥端口共用该结构体。<br />每个桥端口中的表项都有一个桥中的`master`表项与之相对应。 |

### 标识位

| 标识位                   | 解释                                                         |
| ------------------------ | ------------------------------------------------------------ |
| BRIDGE_VLAN_INFO_MASTER  | 添加到桥的`net_bridge_vlan_group{}`组中，有两种可能：<br />1. 作为桥端口指向的`master vlan`存在，并不实际在桥上生效 <br />2. 在桥上实际生效 |
| BRIDGE_VLAN_INFO_BRENTRY | 表示实际在桥上生效                                           |



## Q&A

* `vlan` 设备和`br_vlan` 之间的区别和联系？

  `vlan` 设备是一种虚拟设备，可以在桥之外的情况下使用，用于处理带`vlan tag`的报文；`br_vlan` 只能在桥的时候使用。

  `vlan` 设备只能处理带`vlan tag`的报文，同样也只能发送带`vlan tag` 的报文；`br_vlan` 类似与交换机，可以处理带`vlan tag`的报文，不带`vlan tag` 的报文(PVID)，同时可以发送不带`vlan tag`的报文，相比较`vlan` 设备，更加灵活。



## TODO

* `vlan` 设备和`br_vlan` 同时使用的场景，等到遇到的时候再分析。



## 附录

### 常用命令

```bash
# 配置桥
ip link add br-dev type bridge vlan_filtering 1
ip link set dev eth1 master br-dev

# 桥添加vlan
bridge vlan add dev eth1 vid 10 master
```

