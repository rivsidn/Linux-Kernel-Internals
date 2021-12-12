创建一个`udp socket` 时，`socket` 何时插入到`udp_table` 的哈希表中。



## 执行脚本

通过进程号过滤进程的调用函数。

```bash
#!/bin/bash

tracefs="/sys/kernel/debug"
echo nop > $tracefs/tracing/current_tracer
echo 0 > $tracefs/tracing/tracing_on
echo $$ > $tracefs/tracing/set_ftrace_pid
echo function > $tracefs/tracing/current_tracer
echo 1 > $tracefs/tracing/tracing_on
exec "$@"
```

该脚本主要用于展示如何获取并设置进程号到`set_ftrace_pid` 中，后续我们可以根据需要修改这个脚本。


