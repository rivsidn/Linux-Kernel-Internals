以`4.19.190`内核示例中 `sockex1` 为例，追踪`bpf` 程序执行流程。

## BPF prog

### 程序加载

```strace
bpf(BPF_PROG_LOAD, {prog_type=BPF_PROG_TYPE_SOCKET_FILTER, insn_cnt=15, insns=0x563aca136e80, license="GPL", log_level=0, log_size=0, log_buf=0, kern_version=0, prog_flags=0}, 72) = 5
```

### 程序绑定

```strace
setsockopt(3, SOL_SOCKET, SO_ATTACH_BPF, [5], 4) = 0
```

`socket` 绑定 `BPF` 程序。

### 程序执行

```c
sk_filter()-->sk_filter_trim_cap()-->bpf_prog_run_save_cb()-->BPF_PROG_RUN()

//BPF_PROG_RUN() 定义
#define BPF_PROG_RUN(filter, ctx)  (*(filter)->bpf_func)(ctx, (filter)->insnsi)
```





## BPF map









## 附录

### trace程序执行

以`sockex1` 为例。

````bash
# strace 追踪系统调用
strace ./sockex1
# ftrace 追踪内核执行
mount -t tracefs nodev /sys/kernel/tracing

```bash
#!/bin/bash

tracefs="/sys/kernel"
echo nop > $tracefs/tracing/current_tracer
echo 0 > $tracefs/tracing/tracing_on
echo $$ > $tracefs/tracing/set_ftrace_pid
echo function > $tracefs/tracing/current_tracer
echo 1 > $tracefs/tracing/tracing_on
exec "$@"
```
````

### TODO

* 创建`MAP`
  * 程序执行时候，创建的`MAP`是否可以共享
    * BPF_MAP_GET_FD_BY_ID
* 挂载程序
  * 程序执行时，挂载的程序是否可以共享
    * BPF_PROG_GET_FD_BY_ID







