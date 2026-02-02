
基于 2.6.35.6 内核.


## 使能kgdb

### 进入kdb

- 设置启动参数

  ```
  kgdboc=ttyS0,115200
  ```

- 进入kdb

  ```bash
  echo ttyS0 > /sys/module/kgdboc/parameters/kgdboc
  echo g > /proc/sysrq-trigger
  ```

### 切换到kdgb

```bash
[0]kdb> kgdb
Entering please attach debugger or use $D#44+ or $3#33
```

### 回到kdb

输入 `$3#33` 即可。


## 远程调试

```bash
gdb vmlinux
# 设置波特率
(gdb) set serial baud 115200
(gdb) target remote /dev/ttyUSB0
```

PC 通过GDB 访问设备，远程调试。


## 附录

### 参考资料

[Using kgdb, kdb and the kernel debugger internals](https://www.kernel.org/doc/html/v4.15/dev-tools/kgdb.html)

### FAQ

- 为什么有时候无法添加断点

  **注意：如果设置了CONFIG_DEBUG_RODATA 无法添加断点。**

