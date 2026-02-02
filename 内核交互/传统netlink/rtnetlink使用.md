
## 内核实现

### 

```c
// 函数原型
void rtnl_register(int protocol, int msgtype,
		   rtnl_doit_func doit, rtnl_dumpit_func dumpit,
		   rtnl_calcit_func calcit)
{
	if (__rtnl_register(protocol, msgtype, doit, dumpit, calcit) < 0)
		panic("Unable to register rtnetlink message handler, "
		      "protocol = %d, message type = %d\n",
		      protocol, msgtype);
}
EXPORT_SYMBOL_GPL(rtnl_register);
```

```c
    // 注册
	rtnl_register(PF_UNSPEC, RTM_GETLINK, rtnl_getlink,
		      rtnl_dump_ifinfo, rtnl_calcit);
```

| 函数参数 | 说明                                                   |
|----------|--------------------------------------------------------|
| protocol | 协议类型, ifinfomsg ifi_family 中设置                  |
| msgtype  | 消息类型, nlmsghdr nlmsg_type 中设置                   |
| doit     | 处理函数, nlmsghdr nlmsg_flags 没设置NLM_F_DUMP 时调用 |
| dumpit   | 处理函数, nlmsghdr nlmsg_flags 设置了NLM_F_DUMP 时调用 |
| calcit   | 处理函数, 内部调用，用户无法直接调用                   |


## 重要结构体

### sockaddr_nl

netlink socket 地址.

```c
struct sockaddr_nl {
	__kernel_sa_family_t	nl_family;	/* AF_NETLINK	*/
	unsigned short          nl_pad;     /* zero		*/
	__u32		            nl_pid;     /* port ID	*/
    __u32		            nl_groups;  /* multicast groups mask */
};
```

### nlmsghdr

netlink 消息头.

```c
struct nlmsghdr {
	__u32		nlmsg_len;      /* Length of message including header */
	__u16		nlmsg_type;     /* Message content */
	__u16		nlmsg_flags;	/* Additional flags */
	__u32		nlmsg_seq;	    /* Sequence number */
	__u32		nlmsg_pid;	    /* Sending process port ID */
};
```

#### nlmsg_flags


### rtnetlink

#### rtattr

rt netlink 属性.

```c
struct rtattr {
	unsigned short	rta_len;
	unsigned short	rta_type;
};
```

#### ifinfomsg

rtnetlink network interface 消息头.

```c
struct ifinfomsg {
	unsigned char   ifi_family;
	unsigned char   __ifi_pad;
	unsigned short  ifi_type;		    /* ARPHRD_* */
	int             ifi_index;		    /* Link index	*/
	unsigned        ifi_flags;		    /* IFF_* flags	*/
	unsigned        ifi_change;		    /* IFF_* change mask */
};
```


