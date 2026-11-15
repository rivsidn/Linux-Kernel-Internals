
## 核心文件

```makefile
ip_set-y := ip_set_core.o ip_set_getport.o pfxlen.o
```

| 文件             | 主要职责               |
|------------------|------------------------|
| ip_set_core.c    | 集合框架；用户接口     |
| ip_set_getport.c | 从数据包提取协议和端口 |
| pfxlen.c         | 辅助计算网段           |


## 核心结构体

网络命名空间
  └─ ip_set_net.ip_set_list[id] → ip_set（一个具体集合）
                                  ├─ type → ip_set_type（类型定义）
                                  ├─ variant → ip_set_type_variant（操作函数）
                                  └─ data → bitmap/hash/list 的私有数据

| 结构体                     | 作用                                                                                           |
|----------------------------|------------------------------------------------------------------------------------------------|
| struct ip_set_net          | 每个网络命名空间的集合表                                                                       |
| struct ip_set              | 一个集合实例，用户态通过 ipset create 命令添加                                                 |
| struct ip_set_type         | 集合类型的定义，例如 hash:ip                                                                   |
| struct ip_set_type_variant | hash、bitmap 等具体操作的函数表                                                                |
| struct ip_set_ext          | 元素操作时传递的附加信息，如超时、包/字节计数、注释和 skb 信息                                 |



