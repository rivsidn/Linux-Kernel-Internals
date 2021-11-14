分析 `linux-2.6.35.6` 内核中 `struct net_device{}` 中 `ip_ptr` 指针RCU 的使用。



```c
static struct in_device *inetdev_init(struct net_device *dev)
{
    //设置内存
	rcu_assign_pointer(dev->ip_ptr, in_dev);
    //...
}
```



```c
static inline struct in_device *__in_dev_get_rcu(const struct net_device *dev)
{
    struct in_device *in_dev = dev->ip_ptr;
    if (in_dev) {
        in_dev = rcu_dereference(in_dev);
    }
	return in_dev;
}
static int arp_construcror(struct neighbour *neigh)
{
    //代码临界区
    rcu_read_lock();
    in_dev = __in_dev_get_rcu(dev);
    if (!in_dev) {
        rcu_read_unlock();
        return -EINVAL;
    }
    rcu_read_lock();
    //...
}
```





```c
static void in_dev_rcu_put(struct rcu_head *head)
{
    struct in_device *idev = container_of(head, struct in_device, rcu_head);
	//释放引用计数，当引用计数为 0 的时候释放内存
    in_dev_put(idev);
}

static void inetdev_destroy(struct in_device *in_dev)
{
    //后续的代码没法通过该指针访问这部分内存
    dev->ip_ptr = NULL;
    //已经访问的可以继续访问，只有当代码不在临界去运行时，才会调用 in_dev_rcu_put()
    call_rcu(&in_dev->rcu_head, in_dev_rcu_put);
    //...
}
```



## FAQ

* `rcu_assign_pointer()` 和 `rcu_dereference()` 使用？这两个有什么作用？

  发布、订阅模式，确保在一个CPU上修改的值能立即被另一个CPU获取到。

  

