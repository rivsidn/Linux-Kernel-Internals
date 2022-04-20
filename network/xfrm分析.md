## 重要数据结构

### xfrm_input_afinfo

```c
struct xfrm_input_afinfo {
	unsigned int		family;
	struct module		*owner;
	int					(*callback)(struct sk_buff *skb, u8 protocol, int err);
};
```

### xfrm_state_afinfo

```c
struct xfrm_state_afinfo {
    
};
```

### xfrm_mode

```c
struct xfrm_mode {
    
};
```



### xfrm4_protocol

`xfrm` 协议处理函数。

```c
struct xfrm4_protocol {
	//处理函数，收包时调用
	int (*handler)(struct sk_buff *skb);
	//
	int (*input_handler)(struct sk_buff *skb, int nexthdr, __be32 spi, int encap_type);
	int (*cb_handler)(struct sk_buff *skb, int err);
	int (*err_handler)(struct sk_buff *skb, u32 info);

	struct xfrm4_protocol __rcu *next;
	int priority;
};
```







## TODO

* `CONFIG_NET_IPVTI` 用处？
* `xfrm_state_afino` 结构体作用？
* 















> obj-$(CONFIG_XFRM) := xfrm_policy.o xfrm_state.o xfrm_hash.o \
> 		      xfrm_input.o xfrm_output.o \
> 		      xfrm_sysctl.o xfrm_replay.o
> obj-$(CONFIG_XFRM_STATISTICS) += xfrm_proc.o
> obj-$(CONFIG_XFRM_ALGO) += xfrm_algo.o
> obj-$(CONFIG_XFRM_USER) += xfrm_user.o
> obj-$(CONFIG_XFRM_IPCOMP) += xfrm_ipcomp.o



| 文件名      | 解释                |
| ----------- | ------------------- |
| xfrm_proc.c | 显示ipsec 统计信息  |
| xfrm_user.c | xfrm 用户态配置接口 |
|             |                     |



## 附录

