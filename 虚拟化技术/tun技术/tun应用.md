
- 添加网口

  ```bash
  # 网口添加
  ip tuntap add dev <eth-name> mode tun user "$USER"

  # 网口删除
  ip tuntap del dev <eth-name> mode tun user "$USER"
  ```

- 用户态

  Linux 发送到TUN 的报文可以被用户态程序读到；用户态程序可以用写的方式通过TUN 向外发送报文.

  和TAP 网卡的区别是，TUN 通过用户态发包的时候，不需要写 MAC 地址。

  交给程序的是纯 IP 包，最后一步的 MAC 地址由 Linux 内核根据路由和 ARP/邻居表自动补上，
  用户态 VPN 程序通常不需要自 己构造以太网头。

  TUN 更像“把一条 IP 路由交给程序处理”；TAP 更像“把一根虚拟网线交给程序处理”。
