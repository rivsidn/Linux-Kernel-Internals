## 代码分析









## TODO

* `netfilter` `addrtype`  用法？





## 附录

### 基本配置

```bash
# 官方示例配置
# eth0口上来，目的端口为80的tcp包不建立会话
iptables -t raw -A PREROUTING -i eth0 -p tcp --dport 80 --syn -j NOTRACK
# eth0口上来，目的端口为80的tcp包，如果状态为UNTRACKED,INVALID 则进入代理
iptables -A INPUT -i eth0 -p tcp --dport 80 -m state --state UNTRACKED,INVALID -j SYNPROXY --sack-perm --timestamp --mss 1480 --wscale 7 --ecn
# 设置严格状态检测，第一个不是syn 包的tcp报文过来不会建立会话
echo 0 > /proc/sys/net/netfilter/nf_conntrack_tcp_loose

# 演化配置添加规则
/sbin/iptables -t raw -A PREROUTING -p tcp -m tcp --syn -m addrtype ! --dst-type LOCAL -j NOTRACK
/sbin/iptables -I FORWARD -p tcp -m conntrack --ctstate INVALID,UNTRACKED -j SYNPROXY --sack-perm --timestamp --wscale 7 --mss 1460
# 数值设置
echo 0 > /proc/sys/net/netfilter/nf_conntrack_tcp_loose
```



### 参考资料

* [连接跟踪之synproxy](https://segmentfault.com/a/1190000020651221)

