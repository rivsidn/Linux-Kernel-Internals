## 安装虚拟机

`virtual machine manager`图形界面安装虚拟机。

此处选择的是安装`ubuntu-16.04.1-server`，可以在安装过程中选择`openssh-server`，系统安装好之后可以直接链接`SSH`。



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



## 内核编译环境准备

希望能够在宿主机中使用虚拟机的编译工具链编译内核，这样的好处是：

1. 可以本地编辑代码，工具比较熟悉
2. 本地编译能有较高的性能
3. 过程比较容易控制

实现方式为：

* 首先将内核代码导入虚拟机中，确保在虚拟机环境下内核可以正常编译通过
* 到处内核编译工具链，本地使用



### 虚拟机编译工具链导出













## 附录

### 镜像下载

* [ubuntu 16.04.1 iso download](https://old-releases.ubuntu.com/releases/xenial/ubuntu-16.04.1-server-amd64.iso)



