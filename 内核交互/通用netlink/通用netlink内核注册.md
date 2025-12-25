
| 名词           | 说明                           |
|----------------|--------------------------------|
| 协议族(family) | 对应用户态与内核的通信id       |
| 操作(ops)      | 接受用户态下发命令后执行的动作 |
| 属性(attr)     | 内核、用户态交互的数据类型     |


## 协议族

```c
static struct genl_family genl_demo_family = {
	.id		= GENL_ID_GENERATE,
	.hdrsize	= 0,
	.name		= GENL_DEMO_FAMILY_NAME,
	.version	= GENL_DEMO_VERSION,
	.maxattr	= GENL_DEMO_ATTR_MAX,
};
```

| 成员    | 说明                            |
|---------|---------------------------------|
| id      | GENL_ID_GENERATE 表示自动生成id |
| name    | 名称                            |
| version | 版本号                          |
| maxattr | 属性数量                        |


## 操作

```c
static struct genl_ops genl_demo_ops[] = {
	{
		.cmd	= GENL_DEMO_CMD_ECHO,
		.flags	= 0,
		.policy	= genl_demo_policy,     //二维数组，获取属性类型
		.doit	= genl_demo_echo,
		.dumpit	= NULL,
	},
};
```

### 命令

定义命令.

```c
enum {
	GENL_DEMO_CMD_UNSPEC,
	GENL_DEMO_CMD_ECHO,		/* echo 命令 */
	__GENL_DEMO_CMD_MAX,
};
#define GENL_DEMO_CMD_MAX (__GENL_DEMO_CMD_MAX - 1)
```

## 属性

### 属性枚举

```c
enum {
	GENL_DEMO_ATTR_UNSPEC,
	GENL_DEMO_ATTR_MSG,		/* 消息属性 */
	__GENL_DEMO_ATTR_MAX,
};

#define GENL_DEMO_ATTR_MAX (__GENL_DEMO_ATTR_MAX - 1)
```

### 属性策略

```c
//声明了属性的类型
static struct nla_policy genl_demo_policy[GENL_DEMO_ATTR_MAX + 1] = {
	[GENL_DEMO_ATTR_MSG] = { .type = NLA_NUL_STRING, .len = 256 },
};
```

## 附录

### TODO

- 理解一下这里的用户态程序是怎么编译的

  ```Makefile
  # Makefile for netlink samples

  # 内核模块
  obj-$(CONFIG_SAMPLE_NETLINK) += netlink_demo.o

  # 用户空间测试程序
  hostprogs-$(CONFIG_SAMPLE_NETLINK) := userspace_test

  # 总是编译用户空间程序（无论是 y 还是 m）
  always := $(hostprogs-y) $(hostprogs-m)
  ```

