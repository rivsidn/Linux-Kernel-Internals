
制作docker 镜像，以 `ubuntu 5.10` 为例说明.

## 制作基础根文件系统

```bash
# 工具安装(已安装则忽略)
sudo apt-get update
sudo apt-get install debootstrap
# 生成根文件系统
sudo debootstrap --arch=i386  --variant=buildd --include=make,gcc,build-essential,libncurses5-dev breezy rootfs-i386  http://old-releases.ubuntu.com/ubuntu/
sudo debootstrap --arch=amd64 --variant=buildd --include=make,gcc,build-essential,libncurses5-dev breezy rootfs-amd64 http://old-releases.ubuntu.com/ubuntu/

```

//临时记录
sudo mount -o remount,rw,suid,dev /media/yuchao/SSD1-ext4

## 制作docker镜像

### 创建Dockerfile

```bash
FROM scratch

# 将 Ubuntu 5.10 根文件系统添加到镜像
ADD ubuntu-5.10-rootfs/ /

# 设置环境变量
ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ARG DEBIAN_FRONTEND=noninteractive

# 设置工作目录
WORKDIR /root/
RUN apt-get update

# 安装内核编译工具
RUN apt-get install -y make gcc build-essential libncurses5-dev

# 默认命令
CMD ["/bin/bash"]
```

命令说明.

| 命令    | 说明                                       |
|---------|--------------------------------------------|
| FROM    | 指定镜像起点，类似继承机制                 |
| ADD     | 添加内容到镜像，会自动解压压缩文件         |
| ENV     | 设置环境变量，构建镜像、镜像运行时都会生效 |
| ARG     | 设置环境变量，构建镜像时会生效             |
| WORKDIR | 设置工作目录，构建镜像、镜像运行时生效     |
| RUN     | 运行命令，构建镜像时生效                   |
| CMD     | 设置镜像执行命令                           |

### 构建命令

```bash
sudo docker build -t ubuntu-5.10:latest .
```

## 容器启动

```bash
docker run -it -v /home/yuchao/kernel/linux_stable/.git/workspace/linux-2.6.12:/root ubuntu-5.10
```

命令说明.

| 选项 | 说明             |
|------|------------------|
| -v   | 设置本地文件映射 |
| -it  | 交互方式运行     |


运行之后可以直接在容器中编译内核.


## 容器备份

### 导出文件保存

```bash
# 导出命令

# 导入命令

```

### docker hub



## QEMU启动


```bash
# 图形界面，正常启动流程，需要登陆(直接root即可)
qemu-system-i386 -kernel arch/i386/boot/bzImage -hda /opt/ubuntu-rootfs/ubuntu-5.10/rootfs-i386.img \
-append "root=/dev/hda rw init=/sbin/init console=tty0" -m 256M

# 终端界面，直接登陆bash
qemu-system-i386 -kernel arch/i386/boot/bzImage -hda /opt/ubuntu-rootfs/ubuntu-5.10/rootfs-i386.img \
-append "root=/dev/hda rw init=/bin/bash console=ttyS0" -m 256M -nographic
```

## 附录

### TODO

- 熟悉ubuntu系统启动流程

```
● 看到你的问题了。系统已经启动到 runlevel 2，但是没有在串口上启动登录程序。

  问题诊断

  系统启动正常，但串口上没有 getty（登录服务），所以看不到登录提示符。

  解决方案

  方案1：修改内核参数，直接启动shell（临时测试用）

  qemu-system-i386 -kernel arch/i386/boot/bzImage \
    -hda /opt/ubuntu-rootfs/ubuntu-5.10/rootfs-i386.img \
    -append "root=/dev/hda rw init=/bin/sh console=ttyS0" \
    -m 256M \
    -nographic

  方案2：使用单用户模式

  qemu-system-i386 -kernel arch/i386/boot/bzImage \
    -hda /opt/ubuntu-rootfs/ubuntu-5.10/rootfs-i386.img \
    -append "root=/dev/hda rw single console=ttyS0" \
    -m 256M \
    -nographic

  方案3：修改rootfs配置（永久解决）

  需要在rootfs中配置串口getty。先用方案1或2进入系统，然后：

  1. 对于使用 inittab 的系统（旧版）：
  编辑 /etc/inittab，添加：
  T0:23:respawn:/sbin/getty -L ttyS0 115200 vt100
  2. 对于使用 systemd 的系统（Ubuntu 5.10可能是这个）：
  systemctl enable serial-getty@ttyS0.service
  3. 对于使用 upstart 的系统：
  创建 /etc/init/ttyS0.conf：
  start on runlevel [23]
  stop on runlevel [!23]
  respawn
  exec /sbin/getty -L 115200 ttyS0 vt100

  方案4：快速验证（使用Ctrl+Alt+F1切换）

  如果你想快速测试，可以：
  qemu-system-i386 -kernel arch/i386/boot/bzImage \
    -hda /opt/ubuntu-rootfs/ubuntu-5.10/rootfs-i386.img \
    -append "root=/dev/hda rw init=/sbin/init console=ttyS0" \
    -m 256M \
    -serial mon:stdio
  然后按 Ctrl+A C 进入QEMU监控器，输入 sendkey ctrl-alt-f1

  根本原因

  你的rootfs（Ubuntu 5.10）默认没有在串口上配置getty服务。这是因为：
  - 普通Ubuntu安装默认只在tty1-tty6（VGA控制台）上启动getty
  - 串口（ttyS0）需要手动配置才会有登录提示
```
