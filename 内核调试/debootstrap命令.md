
### 安装命令

```bash
sudo apt install debootstrap
```

### 参数说明

| 参数      | 说明                                         |
|-----------|----------------------------------------------|
| --arch    | 架构                                         |
| --variant | 安装该版本的不同变体，不同变体安装的软件不同 |
| --include | 额外需要安装的软件包，软件包之间使用逗号分割 |


### 命令示例

```bash
debootstrap --arch=i386 --variant=buildd --include=vim --no-check-gpg breezy ubuntu-5.10-i386-bootfs http://old-releases.ubuntu.com/ubuntu/
```

### 重点提示

debootstrap 执行时需要确保输出文件所在的文件系统挂载时没有设置 'nodev' 属性.

debootstrap 执行时需要创建设备文件，如果设置了'nodev' 属性会导致设备文件无法正常
创建.

```bash
# 查看磁盘挂载属性
mount

# 设置了nodev 属性
# tmpfs on /run/snapd/ns type tmpfs (rw,nosuid,nodev,noexec,relatime,size=3208000k,mode=755,inode64)
# 没有设置nodev 属性
# /dev/sda1 on /media/yuchao/SSD1-ext4 type ext4 (rw,relatime,errors=remount-ro,stripe=8191,uhelper=udisks2)

```

如果设置了nodev 属性需要重新挂载.

```bash
sudo mount -o remount,rw,suid,dev /media/yuchao/SSD1-ext4
```

