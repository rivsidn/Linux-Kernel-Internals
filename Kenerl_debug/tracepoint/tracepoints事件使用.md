##　内核编译

```
CONFIG_TRACEPOINTS=y
```

需要确保`tracepoint `　功能开启。



##　挂载tracefs文件系统

```bash
mount -t tracefs nodev /sys/kernel/tracing
```



## 使用

### 重要文件&文件夹

| 文件名           | 作用                                                         |
| ---------------- | ------------------------------------------------------------ |
| trace            | 调试信息输出目标文件                                         |
| tracing_on       | 调试信息输出开关(开关打开后会将信息输出到trace文件中)        |
| available_events | 现存的事件列表                                               |
| set_event        | 事件设置接口                                                 |
| set_event_pid    | 事件过滤，只显示特定进程号的输出信息                         |
| tracing_cpumask  | 事件过滤，只显示特定CPU的输出信息                            |
| events/          | 事件目录，所有的事件以文件的形式存储在该文件夹下，<br/>事件使能可以直接设置对应事件下的`enable`文件为 1 |
|                  |                                                              |



### 应用示例

```bash
# 关闭输出开关(默认开启)
echo 0 > tracing_on
# 开启监听netif_rx 事件
echo 1 > events/net/netif_rx/enable
# 开启输出开关
echo 1 > tracing_on
```

输出内容如下：

```
root@yuchao:/sys/kernel/tracing# cat trace
# tracer: nop
#
# entries-in-buffer/entries-written: 80/80   #P:2
#
#                              _-----=> irqs-off
#                             / _----=> need-resched
#                            | / _---=> hardirq/softirq
#                            || / _--=> preempt-depth
#                            ||| /     delay
#           TASK-PID   CPU#  ||||    TIMESTAMP  FUNCTION
#              | |       |   ||||       |         |
      sd-resolve-906   [000] .... 33598.016106: netif_rx: dev=lo skbaddr=00000000c07bf1ee len=71
      sd-resolve-906   [000] .... 33598.016131: netif_rx: dev=lo skbaddr=0000000077649736 len=71
 systemd-resolve-904   [001] .... 33598.016316: netif_rx: dev=lo skbaddr=00000000018b9789 len=71
 systemd-resolve-904   [001] .... 33598.016451: netif_rx: dev=lo skbaddr=00000000eebf3265 len=71
      sd-resolve-906   [000] .... 33598.016574: netif_rx: dev=lo skbaddr=00000000fce3ea8c len=71
      sd-resolve-906   [000] .... 33598.016595: netif_rx: dev=lo skbaddr=000000005895939e len=71
 systemd-resolve-904   [001] .... 33598.016758: netif_rx: dev=lo skbaddr=000000000e81a5eb len=71
 systemd-resolve-904   [001] .... 33598.016869: netif_rx: dev=lo skbaddr=0000000027ca8796 len=71
      sd-resolve-906   [001] .... 33598.017444: netif_rx: dev=lo skbaddr=0000000026a87f30 len=71
```



## 拓展延伸

其他`filter` 、`trigger`　功能参考内核文档。

