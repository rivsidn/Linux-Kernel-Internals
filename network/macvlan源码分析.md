## 模块初始化

* 注册用户态通信接口
* 注册通知链



## 配置下发

### 配置

```bash
# 添加macvlan设备
ip link add link eth1 dev eth1_macvlan type macvlan
# up该设备
ip link set eth1_macvlan up
# 配置ip地址
ip addr add 172.31.3.137/24 dev eth1_macvlan
```



### 设备添加

```bash
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









## 报文上送





## 报文处理

不同模式之间报文处理差异。



## Q&A

* 设备配置时，mac地址是如何获得的？





## 附录

### 调试命令

```bash
# 挂载文件系统
mount -t tracefs nodev /sys/kernel/tracing

echo "*:mod:macvlan" > set_ftrace_filter

echo function_graph > current_tracer

cat trace_pipe

```

### TODO

* macvlan_set_lockdep_class(dev) 使用？
* 

