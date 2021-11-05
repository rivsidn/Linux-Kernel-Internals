```c
	/* Find the first held_lock of current chain */
	hlock_next = hlock;
	for (i = curr->lockdep_depth - 1; i >= 0; i--) {
		hlock_curr = curr->held_locks + i;
		if (hlock_curr->irq_context != hlock_next->irq_context)
			break;
		hlock_next = hlock;
	}
	i++;
	chain->depth = curr->lockdep_depth + 1 - i;
	cn = nr_chain_hlocks;
	while (cn + chain->depth <= MAX_LOCKDEP_CHAIN_HLOCKS) {
		/*
		 * cn == nf_chain_hlocks 时，返回值为 cn；
		 * cn != nf_chain_hlocks 时，返回值为 nr_chain_hlocks
		 * 下边这段代码展开就是:
		 * {
		 * 	nr_chain_hlocks = cn + chain->depth;
		 * 	n = cn;
		 * }
		 */
		n = cmpxchg(&nr_chain_hlocks, cn, cn + chain->depth);
		if (n == cn)
			break;
		cn = n;
	}
	if (likely(cn + chain->depth <= MAX_LOCKDEP_CHAIN_HLOCKS)) {
		chain->base = cn;
		/* TODO: 这个地方的i, j 一定能对应上么？ */
		for (j = 0; j < chain->depth - 1; j++, i++) {
			int lock_id = curr->held_locks[i].class_idx - 1;
			chain_hlocks[chain->base + j] = lock_id;
		}
		chain_hlocks[chain->base + j] = class - lock_classes;
	}
```


```c
	chain->depth = curr->lockdep_depth + 1 - i;
	if (likely(cn + chain->depth <= MAX_LOCKDEP_CHAIN_HLOCKS)) {
		chain->base = cn;
#if 1
		for (j = 0; j < curr->lockdep_depth - i; j++, i++) {
#else
		for (j = 0; j < chain->depth - 1; j++, i++) {
#endif
			int lock_id = curr->held_locks[i].class_idx - 1;
			chain_hlocks[chain->base + j] = lock_id;
		}
		chain_hlocks[chain->base + j] = class - lock_classes;
	}
```


```c

lock_acquire(lock, 0,
            0, 0, 2,
            NULL, _RET_IP_)


lock_acquire(struct lockdep_map *lock, unsigned int subclass,
            int trylock, int read, int check,
            struct lockdep_map *nest_lock, unsigned long i)

__lock_acquire(lock, 0,
              0, 0, 2, irqs_disabled_flags(flags),
              NULL, _RET_IP_,
              0)

__lock_acquire(struct lockdep_map *lock, unsigned subclass,
              int trylock, int read, int check, int hardirqs_off,
              struct lockdep_map *nest_lock, unsigned long ip,
              int references)
```





```c
spin_release(&lock->dep_map, 1, _RET_IP_);

lock_release(l, n, i);

__lock_release(lock, nested, ip);



```





| enum lock_usage_bit{}     |                   | 二进制 | 十进制 |
| ------------------------- | ----------------- | ------ | ------ |
| LOCKDEP_STATE(HARDIRQ)    | USED_IN           | 0000   | 0      |
|                           | USED_IN_READ      | 0001   | 1      |
|                           | ENABLE_STATE      | 0010   | 2      |
|                           | ENABLE_STATE_READ | 0011   | 3      |
| LOCKDEP_STATE(SOFTIRQ)    | USED_IN           | 0100   | 4      |
|                           | USED_IN_READ      | 0101   | 5      |
|                           | ENABLE_STATE      | 0110   | 6      |
|                           | ENABLE_STATE_READ | 0111   | 7      |
| LOCKDEP_STATE(RECLAIM_FS) | USED_IN           | 1000   | 8      |
|                           | USED_IN_READ      | 1001   | 9      |
|                           | ENABLE_STATE      | 1010   | 10     |
|                           | ENABLE_STATE_READ | 1011   | 11     |
| USED                      |                   | 1100   | 12     |



`mark_lock_irq()` 





| 状态位 | 方向位(USED_IN/ENABLE) | 读写位(WRITE/READ) |
| ------ | ---------------------- | ------------------ |
| 中断   |                        |                    |
| 软中断 |                        |                    |
|        |                        |                    |
|        |                        |                    |





```c
# define rcu_read_acquire() \
		lock_acquire(&rcu_lock_map, 0,
					0, 2, 1,
					NULL, _THIS_IP_)

void lock_acquire(struct lockdep_map *lock, unsigned int subclass,
                  int trylock, int read, int check,
                  struct lockdep_map *nest_lock, unsigned long ip)
{
	__lock_acquire(lock, subclass,
                   trylock, read, check,
                   irqs_disabled_flags(flags), nest_lock, ip,
                   0);
}

__lock_acquire(&rcu_lock_map, 0,
               0, 2, 1,
               irqs_disabled_flags(flag), NULL, _THIS_IP_,
               0);
static int __lock_acquire(struct lockdep_map *lock, unsigned int subclass,
		   int trylock, int read, int check,
           int hardirqs_off,struct lockdep_map *nest_lock,unsigned long ip,
		   int references)





# define rcu_read_release()	lock_release(&rcu_lock_map, 1, _THIS_IP_)
```





```c
struct lockdep_map {
	struct lock_class_key		*key;		//key值，可用于查询hash表
	struct lock_class		*class_cache;	//lock_class缓存
	const char			*name;				//名称
#ifdef CONFIG_LOCK_STAT
	int				cpu;
	unsigned long			ip;
#endif
};

```



### read 

0. 跟写互斥
1. 读获取(不允许递归)
2. 读获取(允许递归)

### check

0. 不检查
1. 简单检查(释放，进程推出的时候依然获取锁，等等...)
2. 全面检查



> 1. nf_chain_hlocks = 0;
>    1. cn = nr_chain_hlocks;
>    2. cn + chain->depth <= MAX_LOOKDEP_CHAIN_HLOCKS
>    3. cn == nr_chain_hlocks
>       1. nr_chain_hlocks = cn + chain->depth;
>       2. n = cn;
>    4. 
> 2. 









## 逻辑关系

* `locp_map` 对应于一个 `lock_class` 
* 进程中有





* `lock_map` 和 `lock_class` 之间是一一映射的么？
* 
* 
