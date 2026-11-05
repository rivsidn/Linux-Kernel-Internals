
## 应用

veth 是连接两个网络接口的虚拟网线。



veth 是连接两个网络接口的虚拟网线可以分别放进不同的 network namespace，用于连接不同 namespace 的网络。

namespace A                    namespace B
┌──────────┐                  ┌──────────┐
│ veth-a   │ <--- veth --->   │ veth-b   │
└──────────┘                  └──────────┘

它并不要求两端一定在不同 namespace。刚创建时，两端通常都在当前 namespace；之后可将其中一端
移到容器的 namespace：

host namespace                 container namespace
┌───────────┐                 ┌───────────┐
│ veth-host │ <--- veth --->  │ eth0      │
└───────────┘                 └───────────┘

然后宿主机侧的 veth-host 往往接入 bridge，容器侧的 eth0 则供容器应用使用。

所以：

• namespace：提供网络隔离边界。
• veth：穿过这个边界、连接两侧网络的虚拟链路。
• bridge：将多个 veth 或物理网卡像交换机一样连接起来。



### 配置示例一 - namespace 互联


下面创建两个 network namespace，并用一对 veth 直连。两端配置在同一个网段，因而不需要
bridge、路由或 NAT。


```bash
ns-a                                      ns-b
192.168.100.1/24                          192.168.100.2/24
veth-a  <========== veth pair ==========> veth-b

# 创建两个独立的网络命名空间
sudo ip netns add ns-a
sudo ip netns add ns-b

# 创建 veth pair；创建后两端先都位于当前（通常是宿主机）namespace
sudo ip link add veth-a type veth peer name veth-b

# 将两端分别移动到对应的 namespace
sudo ip link set veth-a netns ns-a
sudo ip link set veth-b netns ns-b

# 启用每个 namespace 的回环接口
# 没有启用 lo 时，部分本地网络服务可能无法正常工作
sudo ip -n ns-a link set lo up
sudo ip -n ns-b link set lo up

# 给 veth 两端分配同一二层网段中的 IPv4 地址
sudo ip -n ns-a addr add 192.168.100.1/24 dev veth-a
sudo ip -n ns-b addr add 192.168.100.2/24 dev veth-b

# 启用 veth 接口，虚拟链路随之建立
sudo ip -n ns-a link set veth-a up
sudo ip -n ns-b link set veth-b up

# 查看 namespace A 中的网卡和地址
sudo ip -n ns-a addr show veth-a

# 从 namespace A 测试到 namespace B 的连通性
sudo ip netns exec ns-a ping -c 3 192.168.100.2

# 反向测试
sudo ip netns exec ns-b ping -c 3 192.168.100.1

# ---------------

# 清理时删除任意一端即可同时删除整对 veth；这里直接删除 namespace 更方便：

# 删除 namespace；其中的 veth 端点也会被删除
sudo ip netns del ns-a
sudo ip netns del ns-b
```





### 配置示例二 - namespace 联host

下面是在宿主机默认 namespace 与一个模拟容器的 network namespace 之间建立 veth 的完整示例。
它让容器侧网卡名为 eth0。

```bash
# 创建一个模拟容器网络空间。
# 注意：这只创建网络隔离环境，不会启动实际的容器进程。
sudo ip netns add container-ns

# 创建一对 veth；创建后两端都暂时位于宿主机 namespace。
sudo ip link add veth-host type veth peer name veth-container

# 将容器侧端点移动进 container-ns。
sudo ip link set veth-container netns container-ns

# 将容器侧端点重命名为 eth0。
# 新 namespace 中通常没有 eth0，因此可直接改名。
sudo ip -n container-ns link set veth-container name eth0

# 启用容器网络空间中的回环接口。
sudo ip -n container-ns link set lo up

# 为宿主机侧 veth 分配地址，并启用接口。
sudo ip addr add 10.200.0.1/24 dev veth-host
sudo ip link set veth-host up

# 为容器侧 eth0 分配同网段地址，并启用接口。
sudo ip -n container-ns addr add 10.200.0.2/24 dev eth0
sudo ip -n container-ns link set eth0 up

# 从容器网络空间测试到宿主机端点的连通性。
sudo ip netns exec container-ns ping -c 3 10.200.0.1

# 从宿主机测试到容器端点的连通性。
ping -c 3 10.200.0.2

结果：

host namespace                         container namespace
10.200.0.1/24                          10.200.0.2/24
┌───────────┐                         ┌───────────┐
│ veth-host │ <------ veth pair ----> │   eth0    │
└───────────┘                         └───────────┘

还可以在该 namespace 中运行网络服务，模拟容器应用：

# 在“容器”中启动一个 HTTP 服务，监听容器 eth0 的 8000 端口。
sudo ip netns exec container-ns python3 -m http.server 8000 --bind 10.200.0.2

# 另开一个终端，从宿主机访问该服务。
curl http://10.200.0.2:8000/

清理：

# 删除宿主机一端会同时删除整对 veth。
sudo ip link del veth-host

# 删除模拟容器的网络空间。
sudo ip netns del container-ns
```





veth（virtual Ethernet）是内核提供的一对虚拟以太网网卡，可把它理解成一根“软件网线”的两端：

namespace A                     namespace B / host
┌─────────┐   send packet        ┌─────────┐
│ veth-a  │ ──────────────────>  │ veth-b  │
└─────────┘  <─────────────────  └─────────┘

一端发送的二层以太网帧，会直接成为另一端收到的帧。它没有真实网卡、PHY 或物理链路，主要用于
连接网络命名空间、容器、网桥、OVS 等。

典型容器网络结构是：

container eth0 ─ veth pair ─ host vethXXXX ─ linux bridge ─ host NIC

容器侧的端点移入容器网络命名空间并改名为 eth0；宿主机侧留在默认命名空间，接入 docker0、CNI
bridge 或 OVS。这样容器看起来像接到一台交换机上的普通机器。

常用操作：

ip link add veth-host type veth peer name veth-ns
ip netns add demo
ip link set veth-ns netns demo

ip link set veth-host up
ip link set veth-ns netns demo name eth0
ip -n demo addr add 10.10.0.2/24 dev eth0
ip -n demo link set eth0 up

再将宿主侧接入网桥：

ip link set veth-host master br0

实现上，Linux 4.19 的驱动在 drivers/net/veth.c (drivers/net/veth.c:179) 中。发送函数
veth_xmit() 通过 priv->peer 找到对端设备，随后将 skb 交给对端接收路径；未启用 XDP 时最终走
netif_rx()，也就是像接收自普通网卡一样进入协议栈。两端设备在创建时互相保存 peer 指针，见
veth_newlink() (drivers/net/veth.c:1076)。

几个重要特性：

• veth 是二层设备，有 MAC、MTU、VLAN、GSO/校验和等网络设备能力。
• 创建时必须成对出现；通过 ip link 删除其中一端时，内核会一并注销配对端，见 veth_dellink()
  (drivers/net/veth.c:1198)。

• 链路状态相互关联：一端关闭会让两端 carrier 关闭。
• 可多队列，且该内核版本支持 XDP；启用后包先经过对端的 XDP/NAPI 路径，而不是直接走普通
  netif_rx()。

• ethtool -S veth-host 可查看 peer_ifindex，帮助确定配对端。

它和 bridge 的角色不同：veth 负责“连接两个网络端点”；bridge 负责“在多个端口间二层转发”。容
器网络通常同时使用两者。

› 如果 veth 在相同的namespace 下，会有什么后果，或者用途么？


• 可以。veth 的两端放在同一个 namespace 完全合法，内核仍会把它们当作一根虚拟网线：

  同一个 host namespace

  veth-a  <------ veth pair ------>  veth-b

  veth-a 发出的帧会从 veth-b 的接收路径进入同一个网络栈，反过来也一样。不会自动产生新的隔离
  边界，也不会自动获得额外的外网连接能力。

  它的主要用途有：

  • 网络功能测试
    可测试路由、ARP、iptables/nftables、TC 限速、XDP、抓包等收发路径。例如在 veth-a 发包，在
    veth-b 抓包。

  • 连接两个二层网络设备
    例如把 veth-a 接到 br-a，把 veth-b 接到 br-b，相当于在两个 Linux bridge 之间接了一根虚拟
    网线：

    br-a -> veth-a <====> veth-b -> br-b

  • 先创建、后迁移
    创建 veth 后，两端默认都在当前 namespace。容器运行时再将一端移进容器 namespace；因此短暂
    地处于同一个 namespace 是正常过程。

  • 模拟多接口主机
    同一台主机可以为 veth-a、veth-b 分配不同 IP，借此模拟两个通过网线直连的网络端点。

  例如：

  # 在当前 namespace 创建一对 veth。
  sudo ip link add veth-a type veth peer name veth-b

  # 配置两端不同 IP。
  sudo ip addr add 10.10.10.1/24 dev veth-a
  sudo ip addr add 10.10.10.2/24 dev veth-b

  # 启用两端。
  sudo ip link set veth-a up
  sudo ip link set veth-b up

  # 明确指定从 veth-a 发起测试。
  ping -I veth-a -c 3 10.10.10.2

  但如果只是想给主机添加一个“本地地址”，通常应使用 lo 或 dummy 设备。veth 的价值在于它有真实
  的对端接收路径，适合模拟“包从一个接口出去，再从另一个接口进入”。

  需要避免把这对 veth 的两端同时错误接入同一个二层广播域，特别是同一个 bridge；广播或未知单
  播可能形成二层环路。


