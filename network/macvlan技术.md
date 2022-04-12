## 模式

### bridge

子接口之间可以直接通信。

### passthru

只允许单个子接口连接主接口，并必须设置成混杂模式。

### private

同一主要接口的子接口之间彼此隔离，不能通信，即使从外部的物理交换机导流，也会被丢弃。

### vepa(virtual ethernet port aggregator)

子接口之间的通信流量需要导到外部支持`802.1Q/VPEA` 功能的交换机上，经由外部交换机转发，再绕回来。



## 配置命令

```bash
# 添加
ip link add link <DEVICE> dev <name> type macvlan mode <mode>
# 删除
ip link del link <DEVICE> dev <name> type macvlan
# 查看所有
ip link show type macvlan 
# 查看单个设备
ip link show <name>

# 其他相关配置命令
# 接口up
ip link set <name> up
```

**DEVICE** ： 表示物理设备

**NAME**：表示虚拟设备名



## 配置示例

**当前没配置成功， 需要进一步去看。**

```bash
ip link add link eth5 dev mac1 type macvlan mode bridge
ip link add link eth5 dev mac2 type macvlan mode bridge

ip netns add ns1
ip netns add ns2

ip link set mac1 netns ns1
ip link set mac2 netns ns2

ip netns exec ns1 ip addr add 192.168.56.122/24 dev mac1
ip netns exec ns1 ip link set mac1 up

ip netns exec ns2 ip addr add 192.168.56.123/24 dev mac2
ip netns exec ns2 ip link set mac2 up

```







## 附录

### 参考资料

* [Linux云网络基础之网卡虚拟化技术macvlan详解](https://ctimbai.github.io/2019/04/01/tech/net/vnet/linux-macvlan/)



