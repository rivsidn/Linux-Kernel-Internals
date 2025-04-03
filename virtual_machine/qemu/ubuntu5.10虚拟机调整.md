## 支持串口-ubuntu5.10

### 修改`/boot/grub/menu.lst`文件

```bash

# 添加串口配置
serial --unit=0 --speed=115200 --word=8 --parity=no --stop=1
terminal --timeout=10 serial console

# 修改kernel 配置
title           Ubuntu, kernel 2.6.12 Default 
root            (hd0,0)
kernel          /boot/vmlinuz root=/dev/hda1 ro quiet splash console=ttyS0,115200n8
initrd          /boot/initrd.img-2.6.12
savedefault
boot

```

### 启用`getty`

```
T0:23:respawn:/sbin/getty -L ttyS0 115200 vt100
```



## 调试前halt住

可以通过在`start_kernel()` 中添加汇编指令将其断住，断住之后通过在GDB中设置`$pc` 跳过该汇编指令即可。

```c
start_kernel()
{
    //...
    asm("1: jmp 1b\n\r");
	//...
}
```

此处使用内联汇编是为了防止GCC 优化，改变原有C 代码逻辑。



## 设置启动脚本

希望进程启动之后，不执行繁杂的用户态进程，直接启动`bash`，直接在`grub`中添加`init=` 指令即可。

该指令会在切换到真实文件系统时生效，覆盖原有的启动命令，执行`init=` 之后的初始化指令。

```bash
title		Ubuntu, kernel 2.6.12 Default 
root		(hd0,0)
kernel		/boot/vmlinuz root=/dev/hda1 ro quiet splash init=/bin/bash console=ttyS0,115200n8
initrd		/boot/initrd.img-2.6.12
savedefault
boot
```



## 其他调整

### 重新挂载文件系统

这样启动之后，根文件系统是只读的，需要重新挂载文件系统使可读写。

```bash
mount -o remount,rw /
```

### 编译找不到`ld`程序



## 附录

### NOTES

* 使能`kvm` 可能会导致设备加断点时候，执行`c` 之后跳不出断点，类似下边这样：

  ```
  Thread 1 hit Breakpoint 1, do_mount (dev_name=0xc0ed0000 <error: Cannot access memory at address 0xc0ed0000>, dir_name=0xffff81007e79a000 "/sys", type_page=0x5ffd90 "", flags=0, data_page=0x5ffd90) at fs/namespace.c:1010
  1010	{
  (gdb) c
  Continuing.
  
  Thread 1 hit Breakpoint 1, do_mount (dev_name=0xc0ed0000 <error: Cannot access memory at address 0xc0ed0000>, dir_name=0xffff81007e79a000 "/sys", type_page=0x5ffd90 "", flags=0, data_page=0x5ffd90) at fs/namespace.c:1010
  1010	{
  (gdb) c
  Continuing.
  
  Thread 1 hit Breakpoint 1, do_mount (dev_name=0xc0ed0000 <error: Cannot access memory at address 0xc0ed0000>, dir_name=0xffff81007e79a000 "/sys", type_page=0x5ffd90 "", flags=0, data_page=0x5ffd90) at fs/namespace.c:1010
  1010	{
  (gdb) c
  Continuing.
  ```
  



### 系统启动顺序

1. `GRUB` 启动的时候，加载内核，加载 initrd.img 并传递给内核

2. 解压并挂载`initrd.img` 作为临时根文件系统

   1. `grub` 获取到的值是如何传入内核的？

      `grub`将文件加载到内存中，通过`INITRD_START`、`INITRD_SIZE` 参数传递给内核，分别指向内存地址和长度。

   2. 传入内核的值是如何被使用的？

      内核启动时候，访问`INITRD_START`、`INITRD_SIZE`，解压该范围内的数据，生成文件放到`rootfs`中。

      1. 如何成为`rootfs`被访问

         `rootfs` 实际就是保存在`struct task_struct{}->fs` 中的一个指针，最开始的时候，将该指针设置为`rootfs`，后续该数值即可以作为根文件系统被访问。 

      2. 如何判断当前文件系统是在`ram`还是磁盘

         可以通过查看当前文件的`struct task_struct{}->fs->rootmnt->mnt_devname` 来查看是否是`ram`。

   3. 如何查看`initrd.img` 文件的内容

      ```bash
      # 查看文件格式
      $ file initrd.img-2.6.12
      initrd.img-2.6.12: gzip compressed data, from Unix, max compression
      # 解压到目录下
      $ zcat ../initrd.img-2.6.12 | cpio -i
      162770 blocks
      $ ls
      bin  conf  etc  init  lib  lib64  modules  sbin  scripts  usr
      ```

3. 执行`/init` 或 `/linuxrc`

4. 加载必要的驱动模块，挂载真实文件系统

5. 切换到真正的文件系统执行

### TODO

* `populate_rootfs()` 函数执行了哪些动作？

  * 解压根文件系统，在`rootfs`中创建对应文件

  后续进程初始化的时候会执行对应相应的初始化脚本，执行初始化动作。

