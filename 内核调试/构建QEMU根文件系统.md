
以 `ubuntu 5.10` 为例说明.

## 制作基础根文件系统

```bash
# 工具安装
sudo apt-get update
sudo apt-get install debootstrap
# 生成根文件系统
sudo debootstrap --arch=i386 breezy ubuntu-5.10-rootfs http://old-releases.ubuntu.com/ubuntu/
```

## 根文件系统构建脚本

构建分两种方式:

- 简单启动，系统启动之后直接启动bash
- 正常启动，按照debian 正常流程启动，需要登陆用户.
  最开始由于没有创建用户，可以直接root 进入.

可以研究正常两个脚本之间差异.

### 简单启动

```bash
#!/bin/bash

# 创建最简单的根文件系统镜像
echo "创建简单根文件系统镜像..."

# 创建镜像
dd if=/dev/zero of=rootfs.img bs=1M count=1024
mkfs.ext3 rootfs.img

# 挂载
mkdir -p mnt-img
sudo mount -o loop rootfs.img mnt-img

# 复制文件系统
echo "复制文件系统..."
sudo cp -a ubuntu-5.10-rootfs/* mnt-img/

# 创建最简单的init - 直接启动bash
#sudo cat > mnt-img/init << 'EOF'
##!/bin/bash
## 挂载必要的文件系统
#/bin/mount -t proc proc /proc
#/bin/mount -t sysfs sysfs /sys
#
## 直接启动bash
#exec /bin/bash
#EOF
#sudo chmod +x mnt-img/init

# 创建必要设备节点
sudo mknod mnt-img/dev/console c 5 1 2>/dev/null
sudo mknod mnt-img/dev/null c 1 3 2>/dev/null

# 卸载
sudo umount mnt-img
rmdir mnt-img

echo "完成！"
```

### 正常启动

```bash
#!/bin/bash

echo "创建可工作的根文件系统..."

# 创建镜像
dd if=/dev/zero of=rootfs_working.img bs=1M count=1024
mkfs.ext3 -F rootfs_working.img

# 挂载
mkdir -p mnt-img
sudo mount -o loop rootfs_working.img mnt-img

# 复制新导出的完整文件系统
echo "复制文件系统..."
sudo cp -a ubuntu-5.10-rootfs/* mnt-img/

# 创建一个简单的init脚本来替代直接运行bash
sudo cat > mnt-img/sbin/init << 'EOF'
#!/bin/sh
echo "Custom init starting..."

# 挂载必要的文件系统
/bin/mount -t proc proc /proc
/bin/mount -t sysfs sysfs /sys
/bin/mount -t devpts devpts /dev/pts

# 设置环境变量
export PATH=/bin:/sbin:/usr/bin:/usr/sbin
export HOME=/root
export TERM=linux

# 显示一些信息
echo "Root filesystem ready"
/bin/hostname localhost
echo "Starting shell..."

# 启动shell
exec /bin/sh
EOF
sudo chmod +x mnt-img/sbin/init

# 确保关键设备节点存在
echo "创建设备节点..."
sudo rm -f mnt-img/dev/console mnt-img/dev/null mnt-img/dev/zero
sudo mknod mnt-img/dev/console c 5 1
sudo mknod mnt-img/dev/null c 1 3
sudo mknod mnt-img/dev/zero c 1 5
sudo mknod mnt-img/dev/tty c 5 0
sudo mknod mnt-img/dev/tty0 c 4 0
sudo mknod mnt-img/dev/tty1 c 4 1

# 创建必要的目录
sudo mkdir -p mnt-img/proc
sudo mkdir -p mnt-img/sys
sudo mkdir -p mnt-img/dev/pts

# 卸载
sudo umount mnt-img
rmdir mnt-img

echo "完成！"
echo ""
echo "使用以下命令启动："
echo "qemu-system-i386 -kernel /home/yuchao/kernel/linux_stable/.git/workspace/Linux-2.6.12/arch/i386/boot/bzImage -hda $(pwd)/rootfs_working.img -append \"root=/dev/hda rw init=/sbin/init console=tty0 console=ttyS0\" -m 256M -nographic"
```

## 附录

### TODO

- 当前`-nographic` 启动有问题，应该是内核编译8250 串口的问题，需要调整内核编译选项，暂时没验证.

