代码实现主要涉及两个文件，`net/ipv4/netfilter/ipt_SYNPROXY.c` 、`net/netfilter/nf_synproxy_core.c`，其中文件`nf_synproxy_core.c`是`ipv4`、`ipv6`公共的代码实现，主要的流程在`ipt_SYNPROXY.c`中。

以下根据附录中**本地配置** 来分析代码。

## 代码分析

```sequence
client -> synproxy: syn
synproxy -> client: syn,ack
client -> synproxy: ack
synproxy -> server: ack
server -> synproxy: syn,ack
synproxy -> client: ack
synproxy -> server: ack
client -> server: data FORWARD
```

`SYNPROXY` 主要实现原理就是，对于客户端发来的`SYN`包，代理先给回复`SYN/ACK`，客户端回复`ACK` 之后，代理才真正的与服务器建立链接。

具体的流程可以参照 **参考资料** 描述。

**注意：当server 回复的SYN,ACK ，设备接收该报文之后，此时该会话在设备上就已经是 ESTABLISHED 状态了。**



## TODO

* 报文何时匹配规则，何时走`netfilter` 钩子函数，为什么？
* `TCP`发包函数流程分析？
* `netfilter` `addrtype`  用法？



## 附录

### 基本配置

#### 官方配置

```bash
# eth0口上来，目的端口为80的tcp包不建立会话
iptables -t raw -A PREROUTING -i eth0 -p tcp --dport 80 --syn -j NOTRACK
# eth0口上来，目的端口为80的tcp包，如果状态为UNTRACKED,INVALID 则进入代理
iptables -A INPUT -i eth0 -p tcp --dport 80 -m state --state UNTRACKED,INVALID -j SYNPROXY --sack-perm --timestamp --mss 1480 --wscale 7 --ecn
# 设置严格状态检测，第一个不是syn 包的tcp报文过来不会建立会话
echo 0 > /proc/sys/net/netfilter/nf_conntrack_tcp_loose
```

#### 本地配置

```bash
# 本地配置添加规则
/sbin/iptables -t raw -A PREROUTING -p tcp -m tcp --syn -m addrtype ! --dst-type LOCAL -j NOTRACK
/sbin/iptables -I FORWARD -p tcp -m conntrack --ctstate INVALID,UNTRACKED -j SYNPROXY --sack-perm --timestamp --wscale 7 --mss 1460
# 数值设置
echo 0 > /proc/sys/net/netfilter/nf_conntrack_tcp_loose
```



### 参考资料

* [连接跟踪之synproxy](https://segmentfault.com/a/1190000020651221)

