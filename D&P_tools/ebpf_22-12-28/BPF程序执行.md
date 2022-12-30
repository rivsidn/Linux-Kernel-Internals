* 创建`MAP`
  * 程序执行结束之后，创建的`MAP` 是否还存在
  * 程序执行时候，创建的`MAP`是否可以共享
    * BPF_MAP_GET_FD_BY_ID
* 挂载程序
  * 程序执行结束之后，挂载的程序是否还存在
  * 程序执行时，挂载的程序是否可以共享
    * BPF_PROG_GET_FD_BY_ID













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







