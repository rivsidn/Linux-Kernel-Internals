## 模块初始化

* 注册通知链
* 注册用户态通信接口

通知链用于当实际的物理设备状态发生改变的时候，虚拟设备能够做出相应调整；用户态通信接口用于与用户态通信。

所以`macvlan` 的配置主要是通过`netlink` 下发到内核态。

可以通过`ftrace` 追踪函数下发流程，参见 [ftrace追踪配置下发](#ftrace追踪配置下发)。



## 重要数据结构

| 数据结构                       | 解释                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| struct macvlan_port {}         | 该结构体与创建虚接口的物理设备一一对应，存储虚接口的链表等信息 |
| struct macvlan_dev {}          | 虚接口 struct net_device{} 中的私有数据                      |
| struct macvlan_source_entry {} | 对应一个macvlan 源地址转发表，`SOURCE` 模式的接口可以通过该表接收流量；<br />该结构体同样链接在`macvlan_port{}` 中。 |
| struct net_device_ops {}       | 驱动下层接口                                                 |

综上，每个创建虚接口的物理接口有一个对应的`macvlan_port{}` 结构体，虚拟接口通过`macvlan_dev{}` 结构体链接在`macvlan_port{}` 下，同样链接在`macvlan_port{}` 结构体下的还有`macvlan_source_entry{}`。



## 报文接收

### 钩子函数

创建`macvlan` 设备的时候，会首先为实际的物理设备创建`macvlan_port{}` 结构体，因为`macvlan` 设备挂在该结构体链表中。

`macvlan_port{}` 结构体在`macvlan_port_create{}` 函数中创建；同时还会在该函数中为物理设备注册`macvlan_handle_frame()`函数，收包的时候，检测到物理设备如果存在钩子函数，报文会被钩子函数处理。

### 收包函数

受上来的报文检测到物理设备有钩子函数，报文会进入到`macvlan_handle_frame()`钩子函数处理。

处理完之后，钩子函数会返回不同的返回指，通知下收包路程如何处理该报文，主要的返回值有以下几种。

| 返回值              | 解释                               |
| ------------------- | ---------------------------------- |
| RX_HANDLER_CONSUMED | 报文被消耗，不需要继续处理         |
| RX_HANDLER_ANOTHER  | 重新走一遍收包流程                 |
| RX_HANDLER_EXACT    | 强制精确匹配，之匹配对应dev 的类型 |
| RX_HANDLER_PASS     | 报文继续往下执行，不做特殊处理     |

### 发包函数

驱动发包的时候，最终会调用到`net_device_ops{}` 中的`ndo_start_xmit` 函数，对应于`macvlan` 设备也就是`macvlan_start_xmit()` 函数，实现的逻辑与其他的流程大同小异，通过虚拟设备找到实际的物理设备，并将报文从实际的物理设备发送出去。



## 附录

### 配置示例

```bash
# 添加macvlan设备
ip link add link eth1 dev eth1_macvlan type macvlan
# up该设备
ip link set eth1_macvlan up
# 配置ip地址
ip addr add 1.1.1.1/24 dev eth1_macvlan
```

### ftrace追踪配置下发

```bash
# 挂载文件系统
mount -t tracefs nodev /sys/kernel/tracing

echo "*:mod:macvlan" > set_ftrace_filter

echo function_graph > current_tracer

cat trace_pipe
```



```bash
Themis(x86):/sys/kernel/tracing# ip link add link eth1 dev eth1_macvlan type macvlan
Themis(x86):/sys/kernel/tracing# cat trace
# tracer: function_graph
#
# CPU  DURATION                  FUNCTION CALLS
# |     |   |                     |   |   |   |
 2)   0.301 us    |  macvlan_validate [macvlan]();
 2)   0.324 us    |  macvlan_setup [macvlan]();
 2)               |  macvlan_newlink [macvlan]() {
 2)               |    macvlan_common_newlink [macvlan]() {
 2)   3.137 us    |      macvlan_init [macvlan]();
 2)   0.312 us    |      macvlan_device_event [macvlan]();
 2)   0.348 us    |      macvlan_fix_features [macvlan]();
 2)   0.072 us    |      macvlan_dev_get_iflink [macvlan]();
 2)   0.108 us    |      macvlan_fix_features [macvlan]();
 2)   0.192 us    |      macvlan_fix_features [macvlan]();
 2)   0.193 us    |      macvlan_device_event [macvlan]();
 2)   0.180 us    |      macvlan_device_event [macvlan]();
 2)   0.168 us    |      macvlan_device_event [macvlan]();
 2) ! 316.479 us  |    }
 2) ! 317.331 us  |  }
 2)   0.097 us    |  macvlan_get_size [macvlan]();
 2)   0.085 us    |  macvlan_dev_get_iflink [macvlan]();
 2)   0.072 us    |  macvlan_dev_get_iflink [macvlan]();
 2)   0.902 us    |  macvlan_dev_get_stats64 [macvlan]();
 2)   0.348 us    |  macvlan_fill_info [macvlan]();
 2)   0.084 us    |  macvlan_get_link_net [macvlan]();
 0)   0.914 us    |  macvlan_dev_get_stats64 [macvlan]();
```



### TODO

* macvlan_set_lockdep_class(dev) 使用？
* list_first_or_null_rcu()

