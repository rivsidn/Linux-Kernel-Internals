
## 安装命令

```bash

# 安装命令
sudo apt install virt-manager qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils

# 添加用户到libvirt组
sudo usermod -aG libvirt $USER

```

### AI

> > sudo usermod -aG libvirt $USER
> >
> > 这个命令的功能
> 
> ● 这个命令的功能是将当前用户添加到 libvirt 组中。
> 
>   具体解释：
>   - usermod - 修改用户账户的命令
>   - -aG libvirt - 将用户追加到 libvirt 组（-a 表示追加，-G 指定组名）
>   - $USER - 环境变量，代表当前登录的用户名
> 
>   作用：加入 libvirt 组后，用户可以管理虚拟机（KVM/QEMU）而无需 sudo 权限。这常用于使用
>    virt-manager、virsh 等虚拟化工具。
> 
>   注意：执行后需要重新登录才能生效。

