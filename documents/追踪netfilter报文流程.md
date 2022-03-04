内核中自带的`TRACE` target 可以实现追踪报文在防火墙规则中数据流向的功能。



## 原理

1. 通过`TRACE` target 可以设置`skb->nf_trace` 标识位
2. 函数`ipt_do_table()` 中针对设置了该标识位的报文会调用`trace_packet()` 函数
3. `trace_pachet()` 函数运作机制？ **TODO**



## 简单示例

### 防火墙规则

```bash
iptables -t filter -A INPUT -s 172.31.3.140/32 -j ACCEPT
iptables -t filter -P INPUT DROP
```

### 设置追踪

```bash
modprobe nf_log_ipv4
iptables -t raw -A PREROUTING -s 172.31.3.140/32 -j TRACE
iptables -t raw -A PREROUTING -s 172.31.3.137/32 -j TRACE
```

### 报文发送

这里我们使用`sendip` 发送模拟报文，此处`172.31.3.136` 为设备IP。

```bash
sudo sendip -v -d 0x1234567890 -p ipv4 -is 172.31.3.140 -id 172.31.3.136 -p udp -us 60000 -ud 60000 172.31.3.136
sudo sendip -v -d 0x1234567890 -p ipv4 -is 172.31.3.137 -id 172.31.3.136 -p udp -us 60000 -ud 60000 172.31.3.136
```

### 消息输出

```bash
# 对应第一条报文
TRACE: raw:PREROUTING:policy:3 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.140 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=61139 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT:rule:1 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.140 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=61139 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
# 对应第二条报文
TRACE: raw:PREROUTING:policy:3 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=17716 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT:policy:2 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=17716 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
```

### 输出解析

| 报文编号 | 表     | 链         | 规则   | 循环次数 | 解析                                                     |
| -------- | ------ | ---------- | ------ | -------- | -------------------------------------------------------- |
| 1        | raw    | PREROUTING | policy | 3        | 走该链默认规则，循环次数为 3 表示在该链中的匹配次数      |
| 1        | filter | INPUT      | rule   | 1        | 走该链第一条配置规则，循环次数为 1 表示该链中匹配了 1 次 |
| 2        | raw    | PREROUTING | policy | 3        | 同上                                                     |
| 2        | filter | INPUT      | policy | 2        | 走链表默认规则，第二次匹配                               |

**Tips：如上所示，报文2 在filter 表INPUT 链中匹配的时候，ACCEPT 规则没匹配上，此时是没有输入日志消息的。**



## 详细示例

### 防火墙规则

```bash
iptables -t filter -N INTPU_SUB
iptables -t filter -A INPUT_SUB -s 172.31.3.140/32 -j ACCEPT

iptables -t filter -A INPUT -j INPUT_SUB
iptables -t filter -P INPUT DROP
```

### 设置追踪

如上。

### 报文发送

如上。

### 消息输出

```bash
# 第一条报文
TRACE: raw:PREROUTING:policy:3 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.140 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=38276 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT:rule:1 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.140 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=38276 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT_SUB:rule:1 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.140 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=38276 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
# 第二条报文
TRACE: raw:PREROUTING:policy:3 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=64913 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT:rule:1 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=64913 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT_SUB:return:2 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=64913 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
TRACE: filter:INPUT:policy:2 IN=eth0 OUT= MAC=00:0d:48:69:2f:a0:70:b5:e8:72:6e:68:08:00 SRC=172.31.3.137 DST=172.31.3.136 LEN=33 TOS=0x00 PREC=0x00 TTL=255 ID=64913 PROTO=UDP SPT=60000 DPT=60000 LEN=13 
```

### 输出解析

| 报文编号 | 表     | 链         | 规则   | 循环次数 | 解析                                             |
| -------- | ------ | ---------- | ------ | -------- | ------------------------------------------------ |
| 1        | raw    | PREROUTING | policy | 3        | 同上                                             |
| 1        | filter | INPUT      | rule   | 1        | 匹配了第一条规则，即跳转到子链执行               |
| 1        | filter | INPUT_SUB  | rule   | 1        | 匹配了子链中的第一条规则                         |
| 2        | raw    | PREROUTING | policy | 3        | 同上                                             |
| 2        | filter | INPUT      | rule   | 1        | 匹配了第一条规则，即跳转到子链执行               |
| 2        | filter | INPUT_SUB  | return | 2        | 子链中返回，之前尝试匹配了一条规则，没能匹配     |
| 2        | filter | INPUT      | policy | 2        | 执行链默认动作，之前尝试匹配了一条规则，没能匹配 |



## 附录

### 日志解析

| 标识   | 解析           |
| ------ | -------------- |
| policy | 链默认规则     |
| rule   | 下发的配置规则 |
| return | 子链表中返回   |









