基于`linux-2.6.35.6` 内核。



## 重要结构体

```c
/* tracepoint 结构体 */
struct tracepoint {
    const char *name;
    int state;
    void (*regfunc)(void);
    void (*unregfunc)(void);
    struct tracepoint_func *funcs;
} __attribute__((aligned(32)));

/* tracepoint 执行函数 */
struct tracepoint_func {
    void *func;
    void *data;
};

/*
 * 该结构体通过 hlist 挂载到 hash 表中，实际操
 * 作过程中都是先在该结构体上操作，然后update 到 tracepoint 中
 */
struct tracepoint_entry {
    struct hlist_node hlist;
    struct tracepoint_func *funcs;
    int refcount;
    char name[0];
}
/*
 * tracepoint 存储处理函数的结构体，一个tracepoint 可能会有多个
 * tracepoint_func{}，这些 tracepoint_func{} 挂载在对应的tp_probes{}->probes[]
 * 中。
 */
struct tp_probes {
    union {
        struct rcu_head rcu;
        struct list_head list;
    } u;
    struct tracepoint_func probes[0];
};

/* 迭代器，用于遍历 */
struct tracepoint_iter {
    struct module *module;
    struct tracepoint *tracepoint;
};
```



实际的工作流程就是这样的：

1. 调用`tracepoint_add_probe()`往 `tracepoint{}` 中添加钩子函数的时候，会先查看 `tracepoint_table[]` 中是否存在对应的 `tracepoint_entry{}`，如果没有存在则创建，继续执行后续的操作。
2. 创建之后调用`tracepoint_entry_add_probe()` 添加钩子函数，钩子函数存储在 `tp_probes{}` 中，需要调用`allocate_probes()`申请内存，并设置对应的钩子函数。
3. 执行完以上操作之后，只是在`tracepoint_entry{}` 中更新了钩子函数，并没有实际更新到 `tracepoint{}` 中，需要调用 `tracepoint_update_probes()` 来更新。
4. 同样也会在 `set_tracepoint()` 中设置 `tracepoint{}` 的 state，`_DO_TRACE()`执行的时候会调用。



## FAQ

* `tracepoint_entry{}` 和 `tracepoint{}` 之间的关系？

  `tracepoint{}` 是实际生效的结构体，`tracepoint_entry{}` 可以理解成是`tracepoint{}`的影子，添加钩子函数的时候首先在`tracepoint_entry{}`中添加，然后在通过update 操作，同步给`tracepoint{}`。

* `syscalls.h` 文件中 `TRACE_EVENT_FN()` 宏的实现












