
## 使用

### 启动qemu

使用`kdev debug` 模式调试内核.

```bash
kdev_run debug
```

### 启动gdb

```bash
$ PYTHONPATH=/home/yuchao/kernel/linux_stable/.git/workspace/Linux-4.4.155/scripts/gdb gdb vmlinux
(gdb) source scripts/gdb/vmlinux-gdb.py 
(gdb) target remote :1234
(gdb) c
Continuing.
(gdb) lx-dmesg 
[    0.000000] b'Initializing cgroup subsys cpuset'
[    0.000000] b'Initializing cgroup subsys cpu'

```

**Tips: 启动 GDB 时需要设置环境变量`PYTHONPATH`.**

## 命令说明

| 命令       | 说明                                    |
|------------|-----------------------------------------|
| lx-dmesg   | gdb 中查看dmesg 信息                    |
| lx-ps      | gdb 中查看当前进程                      |
| lx-symbols | gdb 中[加载模块符号表](#加载模块符号表) |


### 加载模块符号表

```bash
(gdb) lx-symbols 
loading vmlinux
scanning for modules in /workspace/Linux-4.4.155
loading @0xffffffffc0002000: /workspace/Linux-4.4.155/samples/waitqueue/waitqueue_sample.ko
```

通过执行`lx-symbols` 会自动加载模块符号表信息.



## 附录



