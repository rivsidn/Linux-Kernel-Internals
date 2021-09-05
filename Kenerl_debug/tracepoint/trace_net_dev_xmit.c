extern struct tracepoint __tracepoint_net_dev_xmit;
static inline __attribute__((unused)) __attribute__((no_instrument_function))
void trace_net_dev_xmit(struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len)
{
	if (static_key_false(&__tracepoint_net_dev_xmit.key))
		do {
			struct tracepoint_func *it_func_ptr;
			void *it_func; void *__data;
			if (!(cpumask_test_cpu(((({
										typeof(cpu_number) pscr_ret__;
										do {
											const void *__vpp_verify = (typeof((&(cpu_number)) + 0))((void *)0);
											(void)__vpp_verify;
										} while (0);
										switch(sizeof(cpu_number)) {
										case 1:
										pscr_ret__ = ({ typeof(cpu_number) pfo_ret__;
												switch (sizeof(cpu_number)) {
												case 1:
												asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number));
												break;
												case 2:
												asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 4:
												asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 8:
												asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												default:
												__bad_percpu_size();
												}
												pfo_ret__;
												});
										break;
										case 2:
										pscr_ret__ = ({ typeof(cpu_number) pfo_ret__;
												switch (sizeof(cpu_number)) {
												case 1:
												asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number));
												break;
												case 2:
												asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 4:
												asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 8:
												asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												default:
												__bad_percpu_size();
												} pfo_ret__;
												});
										break;
										case 4:
										pscr_ret__ = ({ typeof(cpu_number) pfo_ret__;
												switch (sizeof(cpu_number)) {
												case 1:
												asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number));
												break;
												case 2:
												asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 4:
												asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 8:
												asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												default:
												__bad_percpu_size(); }
												pfo_ret__;
												});
										break;
										case 8:
										pscr_ret__ = ({ typeof(cpu_number) pfo_ret__;
												switch (sizeof(cpu_number)) {
												case 1:
												asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number));
												break;
												case 2:
												asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 4:
												asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												case 8:
												asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number));
												break;
												default:
												__bad_percpu_size(); }
												pfo_ret__;
												});
										break;
										default:
										__bad_size_call_parameter();
										break;
										} pscr_ret__; }))), cpu_online_mask)))
				return; ;
			rcu_read_lock_sched_notrace();
			it_func_ptr = ({ typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *________p1 = (typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *)({ typeof(((&__tracepoint_net_dev_xmit)->funcs)) _________p1 = ({ union { typeof(((&__tracepoint_net_dev_xmit)->funcs)) __val; char __c[1]; } __u; if (1) __read_once_size(&(((&__tracepoint_net_dev_xmit)->funcs)), __u.__c, sizeof(((&__tracepoint_net_dev_xmit)->funcs))); else __read_once_size_nocheck(&(((&__tracepoint_net_dev_xmit)->funcs)), __u.__c, sizeof(((&__tracepoint_net_dev_xmit)->funcs))); __u.__val; }); do { } while (0); (_________p1); }); do { } while (0); ; ((typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *)(________p1)); });
			if (it_func_ptr) {
				do {
					it_func = (it_func_ptr)->func;
					__data = (it_func_ptr)->data;
					((void(*)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len))(it_func))(__data, skb, rc, dev, skb_len);
				} while ((++it_func_ptr)->func);
			}
			rcu_read_unlock_sched_notrace(); ;
		} while (0);
	if ((0 || 0) && (cpumask_test_cpu(((({ typeof(cpu_number) pscr_ret__; do { const void *__vpp_verify = (typeof((&(cpu_number)) + 0))((void *)0); (void)__vpp_verify; } while (0); switch(sizeof(cpu_number)) { case 1: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 2: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 4: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 8: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; default: __bad_size_call_parameter(); break; } pscr_ret__; }))), cpu_online_mask))) {
		rcu_read_lock_sched_notrace();
		({ typeof(*(__tracepoint_net_dev_xmit.funcs)) *________p1 = (typeof(*(__tracepoint_net_dev_xmit.funcs)) *)({ typeof((__tracepoint_net_dev_xmit.funcs)) _________p1 = ({ union { typeof((__tracepoint_net_dev_xmit.funcs)) __val; char __c[1]; } __u; if (1) __read_once_size(&((__tracepoint_net_dev_xmit.funcs)), __u.__c, sizeof((__tracepoint_net_dev_xmit.funcs))); else __read_once_size_nocheck(&((__tracepoint_net_dev_xmit.funcs)), __u.__c, sizeof((__tracepoint_net_dev_xmit.funcs))); __u.__val; }); do { } while (0); (_________p1); }); do { } while (0); ; ((typeof(*(__tracepoint_net_dev_xmit.funcs)) *)(________p1)); });
		rcu_read_unlock_sched_notrace();
	}
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
void trace_net_dev_xmit_rcuidle(struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len)
{
	if (static_key_false(&__tracepoint_net_dev_xmit.key))
		do {
			struct tracepoint_func *it_func_ptr;
			void *it_func; void *__data;
			if (!(cpumask_test_cpu(((({ typeof(cpu_number) pscr_ret__; do { const void *__vpp_verify = (typeof((&(cpu_number)) + 0))((void *)0); (void)__vpp_verify; } while (0); switch(sizeof(cpu_number)) { case 1: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 2: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 4: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; case 8: pscr_ret__ = ({ typeof(cpu_number) pfo_ret__; switch (sizeof(cpu_number)) { case 1: asm("mov" "b ""%%""gs"":" "%" "1"",%0" : "=q" (pfo_ret__) : "m" (cpu_number)); break; case 2: asm("mov" "w ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 4: asm("mov" "l ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; case 8: asm("mov" "q ""%%""gs"":" "%" "1"",%0" : "=r" (pfo_ret__) : "m" (cpu_number)); break; default: __bad_percpu_size(); } pfo_ret__; }); break; default: __bad_size_call_parameter(); break; } pscr_ret__; }))), cpu_online_mask)))
				return;
			rcu_irq_enter();
			rcu_read_lock_sched_notrace();
			it_func_ptr = ({ typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *________p1 = (typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *)({ typeof(((&__tracepoint_net_dev_xmit)->funcs)) _________p1 = ({ union { typeof(((&__tracepoint_net_dev_xmit)->funcs)) __val; char __c[1]; } __u; if (1) __read_once_size(&(((&__tracepoint_net_dev_xmit)->funcs)), __u.__c, sizeof(((&__tracepoint_net_dev_xmit)->funcs))); else __read_once_size_nocheck(&(((&__tracepoint_net_dev_xmit)->funcs)), __u.__c, sizeof(((&__tracepoint_net_dev_xmit)->funcs))); __u.__val; }); do { } while (0); (_________p1); }); do { } while (0); ; ((typeof(*((&__tracepoint_net_dev_xmit)->funcs)) *)(________p1)); });
			if (it_func_ptr) {
				do {
					it_func = (it_func_ptr)->func;
					__data = (it_func_ptr)->data;
					((void(*)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len))(it_func))(__data, skb, rc, dev, skb_len);
				} while ((++it_func_ptr)->func);
			}
			rcu_read_unlock_sched_notrace();
			rcu_irq_exit();
		} while (0);
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
int register_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data)
{
	return tracepoint_probe_register(&__tracepoint_net_dev_xmit, (void *)probe, data);
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
int register_trace_prio_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data, int prio)
{
	return tracepoint_probe_register_prio(&__tracepoint_net_dev_xmit, (void *)probe, data, prio);
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
int unregister_trace_net_dev_xmit(void (*probe)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len), void *data)
{
	return tracepoint_probe_unregister(&__tracepoint_net_dev_xmit, (void *)probe, data);
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
void check_trace_callback_type_net_dev_xmit(void (*cb)(void *__data, struct sk_buff *skb, int rc, struct net_device *dev, unsigned int skb_len))
{
}

static inline __attribute__((unused)) __attribute__((no_instrument_function))
bool trace_net_dev_xmit_enabled(void)
{
	return static_key_false(&__tracepoint_net_dev_xmit.key);
}

