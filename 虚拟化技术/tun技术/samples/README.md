# 最小 TUN 示例

这个程序只做一件事：读取内核路由到 `tun0` 的 IP 包，并打印源地址、目的地址和协议。
它没有实现 VPN 对端，因此读出的包不会得到回复。

编译：

```bash
make
```

使用脚本创建一个持久 TUN 设备，并配置一个仅用于本机演示的保留网段地址：

```bash
sudo ./setup.sh "$USER" 192.0.2.1/24
```

终端一，以普通用户运行读取程序：

```bash
./tun_reader --iface tun0
```

终端二，向同网段内不存在的地址发送 ping：

```bash
ping -I tun0 192.0.2.2
```

终端一将打印类似：

```text
IPv4: 192.0.2.1 -> 192.0.2.2, protocol 1, 84 bytes
```

`protocol 1` 表示 ICMP。这里没有 ARP 或 MAC 地址，因为 TUN 交给用户态的是三层 IP 包；对比之下，TAP 会交付包含以太网头的二层帧。
