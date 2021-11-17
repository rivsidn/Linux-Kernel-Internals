struct ftrace_raw_kfree_skb {
        struct trace_entry ent;
        void * skbaddr;
        unsigned short protocol;
        void * location;
        char __data[0];
};
static struct ftrace_event_class  event_class_kfree_skb  ;;
static struct ftrace_event_call __attribute__((__used__)) __attribute__((__aligned__(4)))  event_kfree_skb  ;;
struct  ftrace_data_offsets_kfree_skb  {
        ;
};; ;;

static enum print_line_t  ftrace_raw_output_kfree_skb  (struct trace_iterator *iter, int flags, struct trace_event *trace_event) {
        struct ftrace_event_call *event;
        struct trace_seq *s = &iter->seq;
        struct  ftrace_raw_kfree_skb  *field;
        struct trace_entry *entry;
        struct trace_seq *p;
        int ret;
        event = ({
                        const typeof( ((struct ftrace_event_call *)0)->event ) *__mptr = (trace_event);
                        (struct ftrace_event_call *)( (char *)__mptr - __builtin_offsetof(struct ftrace_event_call,event) );
                });
        entry = iter->ent;
        if (entry->type != event->event.type) {
                ({
                 static bool __warned;
                 int __ret_warn_once = !!(1);
                 if (__builtin_expect(!!(__ret_warn_once), 0)) if (({
                                         int __ret_warn_on = !!(!__warned);
                                         if (__builtin_expect(!!(__ret_warn_on), 0)) warn_slowpath_null(  "include/trace/events/skb.h"  ,  36  );
                                         __builtin_expect(!!(__ret_warn_on), 0);
                                         })) __warned = true;
                 __builtin_expect(!!(__ret_warn_once), 0);
                 });
                return TRACE_TYPE_UNHANDLED;
        }
        field = (typeof(field))entry;
        p = &(*({
                                do {
                                } while (0);
                                &(*({
                                                        do {
                                                        const void *__vpp_verify = (typeof((&(ftrace_event_seq))))((void *)0);
                                                        (void)__vpp_verify;
                                                        } while (0);
                                                        ({
                                                         unsigned long __ptr;
                                                         __asm__ ("" : "=r"(__ptr) : "0"((typeof(*(&(ftrace_event_seq))) *)(&(ftrace_event_seq))));
                                                         (typeof((typeof(*(&(ftrace_event_seq))) *)(&(ftrace_event_seq)))) (__ptr + ((({
                                                                                                 typeof(this_cpu_off) pfo_ret__;
                                                                                                 switch (sizeof(this_cpu_off)) {
                                                                                                 case 1: asm("mov" "b ""%%""gs"":%P" "1"",%0" : "=q" (pfo_ret__) : "m" (this_cpu_off));
                                                                                                 break;
                                                                                                 case 2: asm("mov" "w ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                                                 break;
                                                                                                 case 4: asm("mov" "l ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                                                 break;
                                                                                                 case 8: asm("mov" "q ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                                                 break;
                                                                                                 default: __bad_percpu_size();
                                                                                                 } pfo_ret__;
                                                                                                 }))));
                                                         });
                                }));
        }));
        trace_seq_init(p);
        ret = trace_seq_printf(s, "%s: ", event->name);
        if (ret) ret = trace_seq_printf(s, "skbaddr=%p protocol=%u location=%p" "\n", field->skbaddr, field->protocol, field->location);
        do {
        } while (0);
        if (!ret) return TRACE_TYPE_PARTIAL_LINE;
        return TRACE_TYPE_HANDLED;
}
static struct trace_event_functions  ftrace_event_type_funcs_kfree_skb  = { .trace =  ftrace_raw_output_kfree_skb  , };; ;;
static int __attribute__((no_instrument_function))  ftrace_define_fields_kfree_skb  (struct ftrace_event_call *event_call) {
        struct  ftrace_raw_kfree_skb  field;
        int ret;
        ret = trace_define_field(event_call, "void *", "skbaddr", __builtin_offsetof(typeof(field),skbaddr), sizeof(field.skbaddr), (((void *)(-1)) < 0), FILTER_OTHER);
        if (ret) return ret;
        ret = trace_define_field(event_call, "unsigned short", "protocol", __builtin_offsetof(typeof(field),protocol), sizeof(field.protocol), (((unsigned short)(-1)) < 0), FILTER_OTHER);
        if (ret) return ret;
        ret = trace_define_field(event_call, "void *", "location", __builtin_offsetof(typeof(field),location), sizeof(field.location), (((void *)(-1)) < 0), FILTER_OTHER);
        if (ret) return ret;;
        return ret;
};;;

static inline int  ftrace_get_offsets_kfree_skb  ( struct  ftrace_data_offsets_kfree_skb  *__data_offsets, struct sk_buff *skb, void *location) {
        int __data_size = 0;
        struct  ftrace_raw_kfree_skb  __attribute__((unused)) *entry;
        ;
        return __data_size;
};;;

static void  ftrace_raw_event_kfree_skb  (void *__data, struct sk_buff *skb, void *location) {
        struct ftrace_event_call *event_call = __data;
        struct  ftrace_data_offsets_kfree_skb  __attribute__((unused)) __data_offsets;
        struct ring_buffer_event *event;
        struct  ftrace_raw_kfree_skb  *entry;
        struct ring_buffer *buffer;
        unsigned long irq_flags;
        int __data_size;
        int pc;
        do {
                ({
                 unsigned long __dummy;
                 typeof(irq_flags) __dummy2;
                 (void)(&__dummy == &__dummy2);
                 1;
                 });
                do {
                        (irq_flags) = __raw_local_save_flags();
                } while (0);
        } while (0);
        pc = (current_thread_info()->preempt_count);
        __data_size =  ftrace_get_offsets_kfree_skb  (&__data_offsets, skb, location);
        event = trace_current_buffer_lock_reserve(&buffer, event_call->event.type, sizeof(*entry) + __data_size, irq_flags, pc);
        if (!event) return;
        entry = ring_buffer_event_data(event);
        {
                entry->skbaddr = skb;
                if (skb) {
                        entry->protocol = (__builtin_constant_p((__u16)(( __u16)(__be16)(skb->protocol))) ? ((__u16)( (((__u16)(( __u16)(__be16)(skb->protocol)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(skb->protocol)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(skb->protocol)));
                } entry->location = location;;
        } if (!filter_current_check_discard(buffer, event_call, entry, event)) trace_nowake_buffer_unlock_commit(buffer, event, irq_flags, pc);
};

static inline __attribute__((always_inline)) void  ftrace_test_probe_kfree_skb  (void) {
        check_trace_callback_type_kfree_skb  (  ftrace_raw_event_kfree_skb  );
};;

static void  perf_trace_kfree_skb  (void *__data, struct sk_buff *skb, void *location);;
static const char  print_fmt_kfree_skb  [] = "\"" "skbaddr=%p protocol=%u location=%p" "\", " "REC->skbaddr, REC->protocol, REC->location";
static struct ftrace_event_class __attribute__((__used__))  event_class_kfree_skb  = {
        .system = "skb",
        .define_fields =  ftrace_define_fields_kfree_skb  ,
        .fields = { &(event_class_kfree_skb.fields), &(event_class_kfree_skb.fields) },
        .raw_init = trace_event_raw_init,
        .probe =  ftrace_raw_event_kfree_skb  ,
        .perf_probe =  perf_trace_kfree_skb  ,
};;
static struct ftrace_event_call __attribute__((section("_ftrace_events")))  event_kfree_skb  = {
        .name = "kfree_skb",
        .class = &  event_class_kfree_skb  ,
        .event.funcs = &  ftrace_event_type_funcs_kfree_skb  ,
        .print_fmt =  print_fmt_kfree_skb  , };;;

static void  perf_trace_kfree_skb  (void *__data, struct sk_buff *skb, void *location) {
        struct ftrace_event_call *event_call = __data;
        struct  ftrace_data_offsets_kfree_skb  __attribute__((unused)) __data_offsets;
        struct  ftrace_raw_kfree_skb  *entry;
        struct pt_regs __regs;
        u64 __addr = 0, __count = 1;
        struct hlist_head *head;
        int __entry_size;
        int __data_size;
        int rctx;
        perf_fetch_caller_regs(&__regs, 1);
        __data_size =  ftrace_get_offsets_kfree_skb  (&__data_offsets, skb, location);
        __entry_size = ((((__data_size + sizeof(*entry) + sizeof(u32))) + ((typeof((__data_size + sizeof(*entry) + sizeof(u32))))((sizeof(u64))) - 1)) & ~((typeof((__data_size + sizeof(*entry) + sizeof(u32))))((sizeof(u64))) - 1));
        __entry_size -= sizeof(u32);
        if (({
                                static bool __warned;
                                int __ret_warn_once = !!(__entry_size > 2048);
                                if (__builtin_expect(!!(__ret_warn_once), 0)) if (({
                                                        int __ret_warn_on = !!(!__warned);
                                                        if (__builtin_expect(!!(__ret_warn_on), 0)) warn_slowpath_fmt(  "include/trace/events/skb.h"  ,  36  , "profile buffer not large enough");
                                                        __builtin_expect(!!(__ret_warn_on), 0);
                                                        })) __warned = true;
                                __builtin_expect(!!(__ret_warn_once), 0);
                                })) return;
        entry = (struct  ftrace_raw_kfree_skb  *)perf_trace_buf_prepare( __entry_size, event_call->event.type, &__regs, &rctx);
        if (!entry) return;
        {
                entry->skbaddr = skb;
                if (skb) {
                        entry->protocol = (__builtin_constant_p((__u16)(( __u16)(__be16)(skb->protocol))) ? ((__u16)( (((__u16)(( __u16)(__be16)(skb->protocol)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(skb->protocol)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(skb->protocol)));
                } entry->location = location;;
        } head = ({
                        do {
                        const void *__vpp_verify = (typeof((event_call->perf_events)))((void *)0);
                        (void)__vpp_verify;
                        } while (0);
                        ({
                         unsigned long __ptr;
                         __asm__ ("" : "=r"(__ptr) : "0"((typeof(*(event_call->perf_events)) *)(event_call->perf_events)));
                         (typeof((typeof(*(event_call->perf_events)) *)(event_call->perf_events))) (__ptr + ((({
                                                                 typeof(this_cpu_off) pfo_ret__;
                                                                 switch (sizeof(this_cpu_off)) {
                                                                 case 1: asm("mov" "b ""%%""gs"":%P" "1"",%0" : "=q" (pfo_ret__) : "m" (this_cpu_off));
                                                                 break;
                                                                 case 2: asm("mov" "w ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                 break;
                                                                 case 4: asm("mov" "l ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                 break;
                                                                 case 8: asm("mov" "q ""%%""gs"":%P" "1"",%0" : "=r" (pfo_ret__) : "m" (this_cpu_off));
                                                                 break;
                                                                 default: __bad_percpu_size();
                                                                 } pfo_ret__;
                                                                 }))));
                         });
        });
        perf_trace_buf_submit(entry, __entry_size, rctx, __addr, __count, &__regs, head);
};
static inline void  perf_test_probe_kfree_skb  (void) {
        check_trace_callback_type_kfree_skb  (  perf_trace_kfree_skb  );
};;

extern typeof(__tracepoint_kfree_skb) __tracepoint_kfree_skb;
static const char __kstrtab___tracepoint_kfree_skb[] __attribute__((section("__ksymtab_strings"), aligned(1))) = "" "__tracepoint_kfree_skb";
static const struct kernel_symbol __ksymtab___tracepoint_kfree_skb __attribute__((section("__ksymtab" "_gpl"), unused)) = {
        (unsigned long)&__tracepoint_kfree_skb, __kstrtab___tracepoint_kfree_skb
};
