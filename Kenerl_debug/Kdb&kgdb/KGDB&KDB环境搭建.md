本文主要是关注设备调试，PC与设备之间通过串口链接。

## 内核编译

```bash
# CONFIG_STRICT_KERNEL_RWX is not set
CONFIG_FRAME_POINTER=y
CONFIG_KGDB=y
CONFIG_KGDB_SERIAL_CONSOLE=y
CONFIG_KGDB_KDB=y
CONFIG_KDB_KEYBOARD=y		# 不使用键盘的设备可以忽略
```



## kdb 调试

### 进入kdb

```bash
echo ttyS0 > /sys/module/kgdboc/paramters/kgdboc
echo g > /proc/sysrq-trigger
```

### 切换到kdgb

```bash
[0]kdb> kgdb
Entering please attach debugger or use $D#44+ or $3#33
```

### 回到kdb

输入 `$3#33` 即可。



## kgdb 调试

```bash
gdb vmlinux
(gdb) set serial baud 115200
(gdb) target remote /dev/ttyUSB0
```



PC 通过GDB 访问设备，远程调试。



## 参考资料

[Using kgdb, kdb and the kernel debugger internals](https://www.kernel.org/doc/html/v4.15/dev-tools/kgdb.html)

