## 使用

```bash
# 添加规则
/sbin/iptables -t raw -A PREROUTING -p tcp -m tcp --syn -m addrtype ! --dst-type LOCAL -j NOTRACK
/sbin/iptables -I FORWARD -p tcp -m conntrack --ctstate INVALID,UNTRACKED -j SYNPROXY --sack-perm --timestamp --wscale 7 --mss 1460

# 数值设置
echo 0 > /proc/sys/net/netfilter/nf_conntrack_tcp_loose
```



## 代码分析

**TODO**



## 附录

### 参考资料

* [连接跟踪之synproxy](https://segmentfault.com/a/1190000020651221)

