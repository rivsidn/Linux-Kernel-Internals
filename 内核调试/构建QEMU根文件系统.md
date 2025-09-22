
以 `ubuntu 5.10` 为例说明.

## 制作基础根文件系统

```bash
# 生成根文件系统
sudo debootstrap --arch=i386  --variant=buildd --include=make,gcc,build-essential,libncurses5-dev breezy ubuntu-5.10-rootfs http://old-releases.ubuntu.com/ubuntu/
```

## 根文件系统构建脚本

```bash
  #!/bin/bash

  # 创建镜像
  dd if=/dev/zero of=rootfs.img bs=1M count=1024
  mkfs.ext3 rootfs.img

  # 挂载
  mkdir -p mnt-img
  sudo mount -o loop rootfs.img mnt-img

  # 复制文件系统
  sudo cp -a ubuntu-5.10-rootfs/* mnt-img/

  # 卸载
  sudo umount mnt-img
  rmdir mnt-img
```

**Tips:** 创建好的根文件系统拥有者为root，使用的时候需要修改owner.

```bash
sudo chown xxx:xxx rootfs.img
```

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

- 当前`-nographic` 启动有问题，应该是内核编译8250 串口的问题，需要调整内核编译选项，暂时没验证.
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

