#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/livepatch.h>

/* patch 代码 */

#include <linux/net.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <net/snmp.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/route.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <net/arp.h>
#include <net/icmp.h>
#include <net/raw.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <linux/netfilter_ipv4.h>
#include <net/xfrm.h>
#include <linux/mroute.h>
#include <linux/netlink.h>
#include <net/dst_metadata.h>
#ifdef CONFIG_FWOS_BASE
#include <net/kfwlog.h>
#ifdef CONFIG_FWOS_PM
#include <net/time_slice.h>
#endif

#if defined(CONFIG_FWOS_BACKPATH) || defined(CONFIG_FWOS_BACKPATH_MODULE)
#include <net/fwOS.h>
#include <net/netfilter/fastpath/fastpath.h>
#endif

int livepatch_ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt, struct net_device *orig_dev)
{
	const struct iphdr *iph;
	struct net *net;
	u32 len;

	iph = ip_hdr(skb);
	printk("livepatch demo: ip_rcv %pI4-->%pI4\n", &iph->saddr, &iph->daddr);

#ifdef CONFIG_FWOS_PM
	pm_time_stamp();
#endif
	/* When the interface is in promisc. mode, drop all the crap
	 * that it receives, do not try to analyse it.
	 */
	if (skb->pkt_type == PACKET_OTHERHOST)
		goto drop;


	net = dev_net(dev);
	IP_UPD_PO_STATS_BH(net, IPSTATS_MIB_IN, skb->len);

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb) {
		IP_INC_STATS_BH(net, IPSTATS_MIB_INDISCARDS);
		goto out;
	}

	if (!pskb_may_pull(skb, sizeof(struct iphdr)))
		goto inhdr_error;

	iph = ip_hdr(skb);

	/*
	 *	RFC1122: 3.2.1.2 MUST silently discard any IP frame that fails the checksum.
	 *
	 *	Is the datagram acceptable?
	 *
	 *	1.	Length at least the size of an ip header
	 *	2.	Version of 4
	 *	3.	Checksums correctly. [Speed optimisation for later, skip loopback checksums]
	 *	4.	Doesn't have a bogus length
	 */

	if (iph->ihl < 5 || iph->version != 4)
		goto inhdr_error;

	BUILD_BUG_ON(IPSTATS_MIB_ECT1PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_1);
	BUILD_BUG_ON(IPSTATS_MIB_ECT0PKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_ECT_0);
	BUILD_BUG_ON(IPSTATS_MIB_CEPKTS != IPSTATS_MIB_NOECTPKTS + INET_ECN_CE);
	IP_ADD_STATS_BH(net,
			IPSTATS_MIB_NOECTPKTS + (iph->tos & INET_ECN_MASK),
			max_t(unsigned short, 1, skb_shinfo(skb)->gso_segs));

	if (!pskb_may_pull(skb, iph->ihl*4))
		goto inhdr_error;

	iph = ip_hdr(skb);

	if (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		goto csum_error;

	len = ntohs(iph->tot_len);
	if (skb->len < len) {
		IP_INC_STATS_BH(net, IPSTATS_MIB_INTRUNCATEDPKTS);
		goto drop;
	} else if (len < (iph->ihl*4))
		goto inhdr_error;

	/* Our transport medium may have padded the buffer out. Now we know it
	 * is IP we can trim to the true length of the frame.
	 * Note this now means skb->len holds ntohs(iph->tot_len).
	 */
	if (pskb_trim_rcsum(skb, len)) {
		IP_INC_STATS_BH(net, IPSTATS_MIB_INDISCARDS);
		goto drop;
	}

	skb->transport_header = skb->network_header + iph->ihl*4;

	/* Remove any debris in the socket control block */
	memset(IPCB(skb), 0, sizeof(struct inet_skb_parm));

	/* Must drop socket now because of tproxy. */
	skb_orphan(skb);

	return NF_HOOK(NFPROTO_IPV4, NF_INET_PRE_ROUTING,
		       net, NULL, skb, dev, NULL,
		       ip_rcv_finish);

csum_error:
#ifdef CONFIG_FWOS_PM
	pm_time_stamp();
#endif
	IP_INC_STATS_BH(net, IPSTATS_MIB_CSUMERRORS);
inhdr_error:
#ifdef CONFIG_FWOS_PM
	pm_time_stamp();
#endif
	IP_INC_STATS_BH(net, IPSTATS_MIB_INHDRERRORS);
drop:
#ifdef CONFIG_FWOS_PM
	pm_time_stamp();
#endif
	kfree_skb(skb);
out:
	return NET_RX_DROP;
}


static struct klp_func_funcs[] = {
	{
		.old_name = "ip_rcv",
		.new_func = livepatch_ip_rcv,
	}, {}
};

static int livepatch_init(void)
{
	int ret;

	ret = klp_register_patch(&patch);
	if (ret) {
		return ret;
	}
	ret = klp_enable_patch(&patch);
	if (ret) {
		WARN_ON(klp_unregister_patch(&patch));
		return ret;
	}
	return 0;
}

static void livepatch_exit(void)
{
	WARN_ON(klp_disable_patch(&patch));
	WARN_ON(klp_unregister_patch(&patch));
}

module_init(livepatch_init);
module_exit(livepatch_exit);

MODULE_LICENSE("GPL");
