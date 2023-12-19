| 编译环境           | 内核版本       | BusyBox版本    |
| ------------------ | -------------- | -------------- |
| Ubuntu 20.04.4 LTS | linux-4.19.172 | busybox-1.32.1 |



## 前期准备

### 内核编译

```bash
  # 下载内核源代码
  wget http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/linux-4.19.172.tar.gz
  # 需要开启该选项
  CONFIG_DEBUG_INFO=y 
```

### Busybox编译

```bash
  # 下载代码
  wget https://busybox.net/downloads/busybox-1.32.1.tar.bz2
  # 设置静态编译选项
  CONFIG_STATIC=y
  # 编译
  make && make install
```

### 创建启动文件系统

```bash
  # BusyBox目录下
  cd _install
  mkdir proc
  mkdir sys
  touch init
  chmod +x init
  find . | cpio -o --format=newc > ../rootfs.img
```

```bash
  # init内容如下
  #!/bin/sh
  echo "{==DBG==} INIT SCRIPT"
  mkdir /tmp
  mount -t proc none /proc
  mount -t sysfs none /sys
  mount -t debugfs none /sys/kernel/debug
  mount -t tmpfs none /tmp
  
  mdev -s 
  echo -e "{==DBG==} Boot took $(cut -d' ' -f1 /proc/uptime) seconds"
  
  # normal user
  setsid /bin/cttyhack setuidgid 1000 /bin/sh
```



## 内核调试

### Qemu启动内核

```bash
  # 安装依赖软件
  sudo apt-get install qemu qemu-utils qemu-kvm virt-manager libvirt-daemon-system libvirt-clients bridge-utils
  
  # 系统启动
  qemu-system-x86_64 -kernel ./bzImage -initrd  ./rootfs.img -append "nokaslr console=ttyS0" -nographic
  
  # 启动调试
  qemu-system-x86_64 -kernel ./bzImage -initrd  ./rootfs.img -append "nokaslr console=ttyS0" -s -S -nographic
```

**参数说明：**

| 参数                            | 说明                    |
| ------------------------------- | ----------------------- |
| -kernel ./bzImage               | 指定启动的内核镜像      |
| -initrd ./rootfs.img            | 指定启动的文件系统      |
| -append "nokaslr console=ttyS0" | 附加内核启动参数        |
| -s                              | 监听gdb 1234端口        |
| -S                              | 启动后挂起，等待gdb链接 |
| -nographic                      | 不启动图形界面          |

### GDB调试

```bash
[linux-4.19.172]$ gdb 
(gdb) file vmlinux					# 获取内核符号表
(gdb) target remote :1234
(gdb) break start_kernel			# 设备断点
(gdb) c
```



## 附录

### 参考资料

* [使用 GDB + Qemu 调试 Linux 内核](https://www.ebpf.top/post/qemu_gdb_busybox_debug_kernel/)

