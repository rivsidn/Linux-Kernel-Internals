## 模块代码示例

```c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <trace/events/net.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("tracepoint probe demo");

void tracepoint_netif_rx_probe(void * __data, struct sk_buff *skb)
{
	printk("## yuchao debug\n");
	dump_stack();
	return;
}

static int tracepoint_probe_init(void)
{
	int ret = register_trace_netif_rx(tracepoint_netif_rx_probe, NULL);
	if (ret != 0) {
		printk("register probe error\n");
		return -1;
	}

	return 0;
}

static void tracepoint_probe_exit(void)
{
	unregister_trace_netif_rx(tracepoint_probe, NULL);
	tracepoint_synchronize_unregister();
	return;
}

module_init(tracepoint_probe_init);
module_exit(tracepoint_probe_exit);
```



## 内核代码修改

需要在`net/core/net-traces.c` 文件中添加下边这一行，导出符号表，才能在模块中引用。

```c
EXPORT_TRACEPOINT_SYMBOL_GPL(netif_rx)
```



**需要将通过EXPORT_TRACEPOINT_SYMBOL_GPL() 将自己添加的符号表导出才能在模块中引用.**







