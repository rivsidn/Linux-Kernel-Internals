
veth 是连接两个网络接口的虚拟网线，可以分别放进不同的 network namespace，用于连接不同 namespace 的网络。

这里列举几个例子。

- namespace互联
- host-namespace互联

## namespace互联

namespace A                   namespace B
┌──────────┐                  ┌──────────┐
│ veth-a   │ <--- veth --->   │ veth-b   │
└──────────┘                  └──────────┘

```bash
# 创建命名空间
sudo ip netns add ns-a
sudo ip netns add ns-b

# 创建veth
sudo ip link add veth-a type veth peer name veth-b

# 移动veth 到对应的namespace
sudo ip link set veth-a netns ns-a
sudo ip link set veth-b netns ns-b

# 启用每个 namespace 的回环接口
# 没有启用 lo 时，部分本地网络服务可能无法正常工作
sudo ip -n ns-a link set lo up
sudo ip -n ns-b link set lo up

# 分配IPv4 地址
sudo ip -n ns-a addr add 192.168.100.1/24 dev veth-a
sudo ip -n ns-b addr add 192.168.100.2/24 dev veth-b

# 启用veth 接口
sudo ip -n ns-a link set veth-a up
sudo ip -n ns-b link set veth-b up

# 查看IP 地址
sudo ip -n ns-a addr show veth-a
sudo ip -n ns-b addr show veth-b

# 测试连通性
sudo ip netns exec ns-a ping -c 3 192.168.100.2

# 反向测试
sudo ip netns exec ns-b ping -c 3 192.168.100.1

# ---------------

# 删除 namespace；其中的 veth 端点也会被删除
sudo ip netns del ns-a
sudo ip netns del ns-b

```


## host-namespace互联


host namespace                 container namespace
┌───────────┐                 ┌───────────┐
│ veth-host │ <--- veth --->  │ eth0      │
└───────────┘                 └───────────┘

```bash
# 创建一个模拟容器网络空间。
# 注意：这只创建网络隔离环境，不会启动实际的容器进程。
sudo ip netns add container-ns

# 创建一对 veth；创建后两端都暂时位于宿主机 namespace。
sudo ip link add veth-host type veth peer name veth-container

# 将容器侧端点移动进 container-ns。
sudo ip link set veth-container netns container-ns

# 启用容器网络空间中的回环接口。
sudo ip -n container-ns link set lo up

# 为宿主机侧 veth 分配地址，并启用接口。
sudo ip addr add 10.200.0.1/24 dev veth-host
sudo ip link set veth-host up

# 为容器侧 eth0 分配同网段地址，并启用接口。
sudo ip -n container-ns addr add 10.200.0.2/24 dev veth-container
sudo ip -n container-ns link set veth-container up

# 从容器网络空间测试到宿主机端点的连通性。
sudo ip netns exec container-ns ping -c 3 10.200.0.1

# 从宿主机测试到容器端点的连通性。
ping -c 3 10.200.0.2
```

