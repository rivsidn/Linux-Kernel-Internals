
分几步:

1. 查询family id
2. 发送请求
3. 获取回复


## 查询family id

### 发送请求

```c
    memset(&req, 0, sizeof(req));
    req.nlh.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
    req.nlh.nlmsg_type = GENL_ID_CTRL;
    req.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
    req.nlh.nlmsg_seq = *seq;
    req.nlh.nlmsg_pid = getpid();
    
    req.gnlh.cmd = CTRL_CMD_GETFAMILY;
    req.gnlh.version = 1;

    //填充name
    add_attr_string(&req.nlh, sizeof(req), CTRL_ATTR_FAMILY_NAME, GENL_DEMO_FAMILY_NAME);
```

通过名称获取family id.

### 接收解析

```c
// 函数查找属性
static struct nlattr *find_attr(struct nlattr *attrs, int attrlen, int type)
{
	struct nlattr *nla;
	int len = attrlen;

	for (nla = attrs; NLA_ALIGN(nla->nla_len) <= len;
	     nla = (struct nlattr *)((char *)nla + NLA_ALIGN(nla->nla_len))) {
		if (nla->nla_type == type)
			return nla;
		len -= NLA_ALIGN(nla->nla_len);
		if (len < (int)sizeof(*nla))
			break;
	}

	return NULL;
}
```

```c
    gnlh = (struct genlmsghdr *)NLMSG_DATA(nlh);
	nla = find_attr((struct nlattr *)((char *)gnlh + GENL_HDRLEN),
			nlh->nlmsg_len - NLMSG_LENGTH(GENL_HDRLEN),
			CTRL_ATTR_FAMILY_ID);

    //获取family_id
    family_id = *(uint16_t *)NLA_DATA(nla);
```


## 发送命令

```c
	memset(&req, 0, sizeof(req));
	req.nlh.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	req.nlh.nlmsg_type = family_id;
	req.nlh.nlmsg_flags = NLM_F_REQUEST;
	req.nlh.nlmsg_seq = *seq;
	req.nlh.nlmsg_pid = getpid();

    //设置cmd
	req.gnlh.cmd = GENL_DEMO_CMD_ECHO;
	req.gnlh.version = 1;

    //添加属性
    add_attr_string(&req.nlh, sizeof(req), GENL_DEMO_ATTR_MSG, message);
```

## 获取回复

```c
//参见 Linux4.4.155:samples/netlink/generic_netlink/generic_netlink_user.c
```

