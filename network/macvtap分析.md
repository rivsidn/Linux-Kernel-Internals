`macvtap` 与`macvlan` 采用了相同的转发策略，区别是`macvlan` 收的报文会上送到协议栈处理，`macvtap`设备会在用户态创建一个字符设备，通过读取字符设备获取报文。

* 报文进入物理口之后，会通过物理口挂载的钩子函数`macvlan_handle_frame()` 进入到`macvlan` 的收包处理，根据`macvlan` 的收包逻辑判断报文是否应该上送到虚拟设备。

  

  `macvtap_newlink()` -> `macvlan_common_newlinke()`

  在`macvlan_common_newlink()` 函数中给实际的物理设备挂载钩子函数。

* 进入到`macvtap`的报文会通过`macvtap_handle_frame()` 函数，将包文放到`socket` 缓冲队列中。

* 读的时候会从`socket` 缓冲队列获取报文。





## 附录

### 配置命令

```bash
# 配置
ip link add link eth1 name eth1-macvtap type macvtap
# 设置mac地址
ip link set eth1-macvtap address 1a:2b:3c:4d:5e:6a up
# 显示状态
ip link show type macvtap
```



### 参考资料

* [几种常见的网络设备TUN/TAP、MACVLAN、MACVTAP](https://www.pianshen.com/article/37292046010/)

