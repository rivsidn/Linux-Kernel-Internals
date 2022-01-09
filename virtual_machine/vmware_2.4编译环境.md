## 前言

通过`RedHat 7.1` 搭建`2.4` 内核编译环境。

| 用户名  | 密码   |
| ------- | ------ |
| rivsidn | passwd |



## 安装vmware16

* 下载安装包([路径](https://www.vmware.com/cn/products/workstation-pro/workstation-pro-evaluation.html))

* 安装包添加可执行权限并执行安装动作

  ```bash
  chmod 0777 VMware-Workstation-Full-16.1.0-17198959.x86_64.bundle
  sudo ./VMware-Workstation-Full-16.1.0-17198959.x86_64.bundle
  ```



## 安装RedHat 7.1

* 下载镜像([路径](https://soft.lafibre.info/))
* 安装，此时选的是`custome` 模式
  * 避免启动之后的闪屏问题安装的时候可以不选`x windows` `gnome`
  * 选中内核开发可以直接编译内核



## 文件传输

### ftp 模式

* 本地搭建ftp服务器(ssh由于加密算法不匹配不能正常使用)
* 虚拟机通过ftp服务器从本机获取文件

### SSH 模式(推荐)

* 通过`ftp` 将 `openssh-server-2.5.2p2-5.i386.rpm` 传输到虚拟机

* 切换到`root` 用户安装并启动服务

  ```bash
  rpm -i openssh-server-2.5.2p2-5.i386.rpm
  service sshd start
  ```

* 此时外部可以通过下命令链接虚拟机(不添加参数会出现加密算法不匹配问题)

  ```bash
  zssh -oKexAlgorithms=+diffie-hellman-group1-sha1 -o Ciphers=aes256-cbc rivsidn@192.168.249.130
  ```

### nfs 模式(推荐)

* 系统中创建并配置nfs 服务器

  ```bash
  # /etc/exports 中写入
  /home/rivsidn/gitHub *(rw,sync,no_root_squash)
  ```

* 客户端挂载

  ```bash
  sudo mount -t nfs <ipAddress>:/home/rivsidn/gitHub /home/AAA/file
  ```

  

## 编译环境搭建

* 默认的系统中没装gcc，内核编译时候需要装gcc，由于文件依赖，需要按顺序装以下文件(rpm文件在解压的iso文件中找)

  * `kernel-headers-2.4.2-2.i386.rpm`
  * `glibc-devel-2.2.2-10.i386.rpm`
  * `binutils-2.10.91.0.2-3.i386.rpm`
  * `cpp-2.96-81.i386.rpm`
  * `gcc-2.96-81.i386.rpm`

* 内核编译

  ```bash
  # 暂时忽略配置
  make oldconfig
  make
  ```



## 附录

* [old linux镜像下载地址](https://soft.lafibre.info/)

* [系统闪屏问题](https://webhostinggeeks.com/howto/how-to-resolve-init-id-x-respawning-too-fast-disabled-for-5-minutes/)

  