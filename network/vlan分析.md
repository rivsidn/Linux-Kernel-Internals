`linux 4.4.155` 内核中，有两部分内容与`vlan` 相关，一部分是`net/8021q`，另一部分是`net/bridge/br_vlan.c`，此处我们关心的是第一部分的内容。

现在网卡中大都支持`rx-vlan-offload` 和`tx-vlan-offload`，所谓`offload` 意思就是`vlan tag` 操作的功能放到网卡来处理，体现到内核就是：

* `rxvlan` 开启的时候，此时内核中收到报文的`skb->protocol` 设置的是`vlan`  标签去掉之后的协议号
* `txvlan` 开启的时候，报文从内核中通过`vlan_dev_start_xmit()` 将报文发送出去的时候，此时`skb->data`  中并没有带`vlan tag`

关于`rx-vlan-offload` 、`tx-vlan-offload` 和 `reorder_hdr` 之间的关系并没有完全梳理清楚，需要注意的一点是，重新设置这些选项之后，**可能会对抓包造成影响**。我们可以重点关注默认的情况，即`rx-vlan-offload` 、`tx-vlan-offload` 、`reorder_hdr` 全部开启。



## 收发包流程

### 收包

`vlan_do_receive()` 是`vlan` 模块收包函数。

在该函数中将`skb->dev` 设置成对应的`vlan dev` 将保温重新递交上层处理。

### 发包

`vlan_dev_hard_start_xmit()` 是`vlan` 模块发包函数，将报文递交给实际的物理设备发送出去。



所以此处`8021q` 的功能就是，维护`vlan` 相关的内部结构体，报文上来之后，通过协议、`vlan id` 查看对应的`vlan` 设备，如果查找到，则将`skb->dev`设置成`vlan`设备，递交到上层处理；发包时候，找到对应的`vlan` 设置，然后调用`vlan`设备的发包函数，将报文发送出来。

所以这样理解，`vlan` 设备实际上就是一个与原物理设备`mac` 地址相同的虚拟设备，设备可以配置`IP` 地址，接收、发送对应`vlan tag` 的报文。单纯看代码判断，`vlan` 设备没办法发送不带`vlan tag` 的报文，同样的，没带`vlan tag` 的报文上来之后，如果没有对应的`vlan id` 则不会去找对应的`vlan` 设备，自然也就无法与`vlan`设备通信。

综上，`vlan` 设备只能处理带`vlan tag` 的报文，同样的，也只能发送带有`vlan tag` 的报文。



## 重要结构体

**TODO: 用图形表示，如何管理图片**



## Q&A

* 一个物理口上，创建了一个`vlan` 设备，当物理设备、`vlan`设备都配置了相同网段的`IP`地址时，此时`ping` 其中的`IP`地址，可能会发现设备不给回复`ARP`，为什么此时不给回复`ARP`？





## TODO

### 功能流程

* 网口`up`时，将网口添加到`vlan 0`中的作用？需要去看`vlan 0` 的意义
* 邻居子系统
* 网卡gro等功能
* `vlan_gro_receive()`、`vlan_gro_complete()` 作用？
* `gvrp` 与 `garp` 之间工作流程

### API

* skb_push()
* skb_pull()
* dev_add_offload()
* skb_vlan_untag()
* netif_keep_dst()



## 附录

### 配置命令

```bash
ip link add link eth0 type vlan id 2
ip addr add 172.31.3.136/24 dev vlan0
ip link set eth0 up
ip link set vlan0 up

ip link delete vlan0 type vlan id 2

# cat /proc/net/vlan/config 
VLAN Dev name    | VLAN ID
Name-Type: VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD
vlan0          | 2  | eth0

# 设备调试
mount -t tracefs nodev /sys/kernel/tracing
cd /sys/kernel/tracing
echo 'icmp_rcv' > set_ftrace_filter
echo 'icmp_send' >> set_ftrace_filter

# PC配置
sudo ip link add link enp1s0 type vlan id 2
sudo ip addr add 172.31.3.137/24 dev enp1s0
# PC发包
sudo tcpreplay --loop=1 --intf1="enp1s0" icmp_vlan2.pcap

ping -I vlan0 172.31.3.136 -c 1

```

