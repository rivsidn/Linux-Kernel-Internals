
## 配置示例

```bash
# 创建集合
ipset create blocked hash:ip

# 添加表项
ipset add blocked 203.0.113.10

# 查看集合
ipset list blocked

# 规则引用
iptables -I INPUT -m set --match-set blocked src -j DROP
```

**NOTE: src 的意思是用源IP 来匹配blocked 中的表项.**

src、dst 表示的是怎么取报文的信息.


配置流程:

- 创建集合
- 添加表项
- iptables 规则引用

