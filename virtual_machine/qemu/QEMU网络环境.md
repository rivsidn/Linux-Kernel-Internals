
### USER模式

```bash
qemu-system-x86_64 -nographic -kernel bzImage -initrd root.img -smp 2 -netdev user,id=mynet0,hostfwd=udp::12345-:80 -device e1000,netdev=mynet0 -append "root=/dev/ram init=/bin/sh ramdisk=20480 console=ttyS0"
```

设置监听宿主机的 `12345` 端口，映射到虚拟机的 `80` 端口上.

此时宿主机通过`netstat` 查看可以发现`12345` 端口正在被监听.

```bash
$ netstat -unpl | grep 12345
udp        0      0 0.0.0.0:12345           0.0.0.0:*                           7885/qemu-system-x8 
```

TODO: 一直不通.

### TAP模式

* 宿主机网络设置

  ```bash
  # 配置tap0网卡
  sudo tunctl -t tap0 -u root
  # 配置网桥
  sudo brctl addbr brg0
  sudo brctl addif brg0 <nic-name>  		#此处nic-name 为物理网卡名称
  sudo brctl addif brg0 tap0
  # 设置混杂模式
  sudo ip link set brg0 promisc on
  sudo ip link set tap0 promisc on
  sudo ip link set <nic-name> promisc on	#同上
  ```

* 启动命令行
  ```bash
  qemu-system-x86_64 -nographic -kernel bzImage -initrd root.img -m 1024m -smp 2 -netdev tap,id=mynet0,ifname=tap0,script=no,downscript=no -device e1000,netdev=mynet0 -append "root=/dev/ram init=/bin/sh ramdisk=20480 console=ttyS0"
  ```
* 虚拟机配置IP地址

  ```bash
  ip link set eth0 up
  ip addr add <addr> dev eth0
  ```

此时，外部可以ping 通虚拟机.

## 附录

### 参考资料

* [QEMU 网络配置一把梭](https://wzt.ac.cn/2021/05/28/QEMU-networking/)
* [Setting up Qemu with a tap interface](https://gist.github.com/extremecoders-re/e8fd8a67a515fee0c873dcafc81d811c)

