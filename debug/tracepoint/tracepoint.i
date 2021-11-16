# 1 "tmp.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "tmp.c"
# 45 "tmp.c"
extern struct tracepoint __tracepoint_kfree_skb;
static inline void trace_kfree_skb((((struct sk_buff *skb, void *location))))
{
        if (unlikely(__tracepoint_kfree_skb.state)) __DO_TRACE(&__tracepoint_kfree_skb, TP_PROTO(PARAMS(void *__data, PARAMS(TP_PROTO(struct sk_buff *skb, void *location)))), TP_ARGS(PARAMS(__data, PARAMS(TP_ARGS(skb, location))))); }
static inline int register_trace_kfree_skb(void (*probe)(PARAMS(void *__data, PARAMS(TP_PROTO(struct sk_buff *skb, void *location)))), void *data) { return tracepoint_probe_register("kfree_skb", (void *)probe, data); }
static inline int unregister_trace_kfree_skb(void (*probe)(PARAMS(void *__data, PARAMS(TP_PROTO(struct sk_buff *skb, void *location)))), void *data) { return tracepoint_probe_unregister("kfree_skb", (void *)probe, data); }
static inline void check_trace_callback_type_kfree_skb(void (*cb)(PARAMS(void *__data, PARAMS(TP_PROTO(struct sk_buff *skb, void *location))))) { }
# 67 "tmp.c"
 ;
