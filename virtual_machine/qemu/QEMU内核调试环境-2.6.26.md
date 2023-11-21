## 内核编译

### 虚拟机安装

`ubuntu-8.10-server-amd64.iso`

### ubuntu-8.10配置源

```
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-security main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-updates main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-proposed main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-backports main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-security main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-updates main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-proposed main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ intrepid-backports main restricted universe multiverse
```

通过`scp` 命令`cp` 到虚拟机中。

### 安装依赖程序

```bash
sudo apt-get update

# 安装ssh，安装之后，可以登陆后台
sudo apt-get install openssh-server
# 安装编译依赖程序
sudo apt-get install make gcc
sudo apt-get install build-essential
sudo apt-get install libncurses5-dev
```

### 内核编译

```bash
make

# 开启CONFIG_DEBUG_INFO
make menuconfig
```



## 根文件系统制作

### 制作镜像

```
sudo dd if=/dev/zero of=root.img bs=1M count=10
sudo mkfs.ext2 root.img
mkdir mount
sudo mount -t ext2 -o loop root.img mount
```

### 创建字符设备

```
sudo mkdir mount/dev
sudo mknod mount/dev/console c 5 1
sudo mknod mount/dev/ram b 1 0
```

### 编译并安装busybox

* 设置编译选项

  ```bash
  make defconfig
  ```

* 修改编译选项`make menuconfig`

  ```
  # 设置静态编译
  Busybox Settings
  	Build Options
  		Build BusyBox as a static binary(no shared libs)
  # 关闭job control
  Shells
  	Job control
  ```

* 编译安装

  ```bash
  make -j2
  make CONFIG_PREFIX=/home/<xxx>/mount install
  ```

### 卸载文件系统

```bash
sudo umount mount
```



## 系统启动

```bash
qemu-system-x86_64 -nographic -kernel ./bzImage -initrd ./root.img -append "root=/dev/ram init=/bin/sh ramdisk=20480 console=ttyS0"
```



## 附录

### 常见问题

* `ssh` 中执行`make menuconfig`  时报错 `Error opening terminal: xterm-256color.`

  ```bash
  # 解决方法，ssh中执行，之后重新 make menuconfig 即可
  export TERM=linux
  ```

* 启动过程中提示`RAMDISK: image too big! (10240KiB/4096KiB)`

  ```bash
  # 启动选项中添加 ramdisk=20480 即可
  qemu-system-x86_64 -nographic -kernel ./bzImage -initrd ./root.img -append "root=/dev/ram init=/bin/sh ramdisk=20480 console=ttyS0"
  ```



### 参考资料

* [Error opening terminal: xterm-256color](https://stackoverflow.com/questions/6788402/error-opening-terminal-xterm-256color)
* [搭建Linux2.6内核调试环境](https://www.jianshu.com/p/a12c89a4f409)

