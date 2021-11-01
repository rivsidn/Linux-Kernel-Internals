

|                           |                   |      |
| ------------------------- | ----------------- | ---- |
| LOCKDEP_STATE(HARDIRQ)    | USED_IN           | 000  |
|                           | USED_IN_READ      | 001  |
|                           | ENABLE_STATE      | 010  |
|                           | ENABLE_STATE_READ | 011  |
| LOCKDEP_STATE(SOFTIRQ)    | USED_IN           | 100  |
|                           | USED_IN_READ      | 101  |
|                           | ENABLE_STATE      | 110  |
|                           | ENABLE_STATE_READ | 111  |
| LOCKDEP_STATE(RECLAIM_FS) | USED_IN           | 200  |
|                           | USED_IN_READ      | 201  |
|                           | ENABLE_STATE      | 210  |
|                           | ENABLE_STATE_READ | 211  |
| USED                      |                   | 300  |





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