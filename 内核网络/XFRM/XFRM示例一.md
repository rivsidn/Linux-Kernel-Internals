

  设备 A                                             设备 B
  192.0.2.1/24                                      198.51.100.1/24
  默认网关：192.0.2.254                              默认网关：198.51.100.254

  应用数据: 192.0.2.1  ----------------------->  198.51.100.1
                   \_______ ESP 加密保护 _______/

  外层 IP 仍是: 192.0.2.1 -> 198.51.100.1

  前提：

  • 两端公网地址可通过正常路由互通，例如 ping 198.51.100.1。
  • 中间网络和两端防火墙允许 ESP，即 IP 协议号 50。
  • 两端之间没有 NAT。手工 XFRM 不处理 NAT-T。
  • 以下 192.0.2.0/24、198.51.100.0/24 是文档示例网段，替换为实际地址。
  • 请通过串口、控制台或其他带外方式操作。策略安装完成前，当前 SSH 连接可能短暂中断。

  设定两条方向分别使用不同密钥：

  A -> B:
    SPI:      0x100
    AES key:  0x00112233445566778899aabbccddeeff
    HMAC key: 0x00112233445566778899aabbccddeeff102132435465768798a9bacbdcedfe0f

  B -> A:
    SPI:      0x200
    AES key:  0x102132435465768798a9bacbdcedfe0f
    HMAC key: 0xffeeddccbbaa998877665544332211000f1e2d3c4b5a69788796a5b4c3d2e1f0

  在设备 A（192.0.2.1）配置：

  # A -> B：A 的出站 SA
  ip xfrm state add \
    src 192.0.2.1 dst 198.51.100.1 \
    proto esp spi 0x100 mode transport reqid 1 \
    auth-trunc 'hmac(sha256)' 0x00112233445566778899aabbccddeeff102132435465768798a9bacbdcedfe0f 128 \
    enc 'cbc(aes)' 0x00112233445566778899aabbccddeeff

  # B -> A：A 的入站 SA
  ip xfrm state add \
    src 198.51.100.1 dst 192.0.2.1 \
    proto esp spi 0x200 mode transport reqid 1 \
    auth-trunc 'hmac(sha256)' 0xffeeddccbbaa998877665544332211000f1e2d3c4b5a69788796a5b4c3d2e1f0 128 \
    enc 'cbc(aes)' 0x102132435465768798a9bacbdcedfe0f

  # A 发给 B 的包必须使用 ESP
  ip xfrm policy add \
    dir out src 192.0.2.1/32 dst 198.51.100.1/32 \
    tmpl src 192.0.2.1 dst 198.51.100.1 \
    proto esp mode transport reqid 1

  # A 收到并解封的 B -> A 流量必须匹配该 SA
  ip xfrm policy add \
    dir in src 198.51.100.1/32 dst 192.0.2.1/32 \
    tmpl src 198.51.100.1 dst 192.0.2.1 \
    proto esp mode transport reqid 1

  在设备 B（198.51.100.1）配置：

  # A -> B：B 的入站 SA，SPI 必须与 A 出站 SA 相同
  ip xfrm state add \
    src 192.0.2.1 dst 198.51.100.1 \
    proto esp spi 0x100 mode transport reqid 1 \
    auth-trunc 'hmac(sha256)' 0x00112233445566778899aabbccddeeff102132435465768798a9bacbdcedfe0f 128 \
    enc 'cbc(aes)' 0x00112233445566778899aabbccddeeff

  # B -> A：B 的出站 SA，SPI 必须与 A 入站 SA 相同
  ip xfrm state add \
    src 198.51.100.1 dst 192.0.2.1 \
    proto esp spi 0x200 mode transport reqid 1 \
    auth-trunc 'hmac(sha256)' 0xffeeddccbbaa998877665544332211000f1e2d3c4b5a69788796a5b4c3d2e1f0 128 \
    enc 'cbc(aes)' 0x102132435465768798a9bacbdcedfe0f

  # B 发给 A 的包必须使用 ESP
  ip xfrm policy add \
    dir out src 198.51.100.1/32 dst 192.0.2.1/32 \
    tmpl src 198.51.100.1 dst 192.0.2.1 \
    proto esp mode transport reqid 1

  # B 收到并解封的 A -> B 流量必须匹配该 SA
  ip xfrm policy add \
    dir in src 192.0.2.1/32 dst 198.51.100.1/32 \
    tmpl src 192.0.2.1 dst 198.51.100.1 \
    proto esp mode transport reqid 1

  验证：

  ip -s xfrm state
  ip -s xfrm policy
  ping -I 192.0.2.1 198.51.100.1

  A 的外网接口上抓包：

  tcpdump -ni eth0 'ip proto 50'

  正常情况下能看到 ESP（协议号 50）报文，而不是明文 ICMP/TCP/UDP 载荷。
  这个配置是静态密钥教学示例，没有自动协商、重放密钥或密钥轮换；
  正式环境应使用 strongSwan 等 IKE 实现来管理 XFRM。

