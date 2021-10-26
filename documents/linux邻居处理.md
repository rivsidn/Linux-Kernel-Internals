* `arp` 和 `neighbour` 是如何联系起来的？

  `neighbour` 实际上就是一个`arp` 的上层抽象，内核代码中，`arp` 是基于 `neighbour`的，`arp` 中可以直接调用`neighbour` 部分的代码。

  `arp_init()`中，通过`neigh_table_init()` 将`arp_tbl` 注册到`neigh_tables` 中，

* 









## 附录

### TODO

* `hh_cache` 是何时创建的，如何使用的？

  `hh_cache` 在`neigh_hh_init()` 中初始化，`neigh_hh_init()`在函数 `neigh_resolve_output()` 中调用，最开始二层头没缓存，首先会调用`neigh_resolve_output()` 函数，在该函数中，缓存二层头，之后调用就直接调用缓存函数。

* `neigh_invalidate()` 该函数下的两个宏的用处？

* `neigh_create()` 中的 `confirmed` 设置怎么理解？

* 邻居表的状态转换？