## 安装虚拟机

`virtual machine manager`图形界面安装虚拟机。

此处选择的是安装`ubuntu-16.04.1-server`，可以在安装过程中选择`openssh-server`，系统安装好之后可以直接链接`SSH`。

* 安装过程中不要启动`LVM`
* 安装过程中需要启用`GRUB`



### 安装编译工具链

```bash
# 文件传输
sudo apt install lrzsz

# 内核编译
sudo apt install bc gcc make build-essential libncurses5-dev

sudo apt install libssl-dev

```



## 配置GDB调试

启动`gdb`调试需要修改`xml`文件，修改之后需重启虚拟机。

```bash
# 行首添加命名空间
<domain type='qemu' xmlns:qemu='http://libvirt.org/schemas/domain/qemu/1.0'>

# 设置为qemu模式之后需要调整CPU设置
<cpu mode='custom' match='exact' check='full'>
  <model fallback='forbid'>qemu64</model>
  <feature policy='require' name='hypervisor'/>
  <feature policy='require' name='lahf_lm'/>
</cpu>

# 指定监听端口
<qemu:commandline>
  <qemu:arg value='-gdb'/>
  <qemu:arg value='tcp::1234'/>
  <qemu:arg value='-S'/>
</qemu:commandline>
```



## 配置代码同步

```bash
# 虚拟机
mkdir bare_repo_linux-4.4.155
git init --bare

# 宿主机
git remote add ubuntu16.04 rivsidn@<ip>:~/bare_repo_linux-4.4.155
git push ubuntu16.04

# 代码同步
cd linux-4.4.155
git pull ~/bare_repo_linux-4.4.155 master
```















## 附录

### 镜像下载

* [ubuntu 16.04.1 iso download](https://old-releases.ubuntu.com/releases/xenial/ubuntu-16.04.1-server-amd64.iso)



