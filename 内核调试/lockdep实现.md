
基于 2.6.35.6 内核.

## 重要数据结构

### lock_class

锁类，lockdep 中锁的抽象.

通过lockdep_map{} 与具体的锁建立联系.

### held_lock

该结构体用于记录进程获取到的锁，伴随进程锁的获取、释放，进程的这个结构体是动态变化的.

### lock_list

记录锁之间的依赖关系，两个lock_list{} 共同表示lock_class{} 的一条边.


## 附录

### 相关图

- [lock_class锁类](/home/yuchao/github/kernel_graph/2.6.35.6/kernel/lock_class.dia)
- [held_lock](/home/yuchao/github/kernel_graph/2.6.35.6/kernel/held_lock.dia)
- [lock_list锁链表](/home/yuchao/github/kernel_graph/2.6.35.6/kernel/lock_list.dia)
- [lock_chain锁链](/home/yuchao/github/kernel_graph/2.6.35.6/kernel/lock_chain.dia)


### TODO

- `WARN_ONCE()` 内核实现

