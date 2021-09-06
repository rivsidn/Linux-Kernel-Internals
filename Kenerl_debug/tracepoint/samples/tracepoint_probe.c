#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <trace/events/net.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("tracepoint probe demo");

void tracepoint_probe(void * __data, struct sk_buff *skb)
{
	printk("## yuchao debug\n");
	dump_stack();
	return;
}

static int tracepoint_probe_init(void)
{
	int ret = register_trace_netif_rx(tracepoint_probe, NULL);
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

