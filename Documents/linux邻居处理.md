`arp_constructor()` 中的 `rcu_read_lock()` 使用。











## 附录

### TODO

* `arp` 和 `neighbour` 是如何联系起来的？

* `hh_cache` 是何时创建的，如何使用的？

  `hh_cache` 在`neigh_hh_init()` 中初始化，`neigh_hh_init()`在函数 `neigh_resolve_output()` 中调用，最开始二层头没缓存，首先会调用`neigh_resolve_output()` 函数，在该函数中，缓存二层头，之后调用就直接调用缓存函数。

* `neigh_invalidate()` 该函数下的两个宏的用处？

* `neigh_create()` 中的 `confirmed` 设置怎么理解？

* 邻居表的状态转换？