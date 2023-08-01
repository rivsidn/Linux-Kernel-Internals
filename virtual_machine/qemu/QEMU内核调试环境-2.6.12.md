## 内核编译

### 虚拟机安装(vmware)

* 下载`ubuntu 5.10`版本镜像，[下载地址](https://old-releases.ubuntu.com/releases/)
* 调整硬盘为IDE，否则无法正常安装

### 搭建文件传输环境

* 安装ssh服务器

  ```bash
  sudo apt-get install openssh-server
  ```

* 文件传输命令，参见[命令](#常用命令)

### 内核编译

* 设置`sources.list`，参见[源配置](#ubuntu5.10源配置)

  ```bash
  sudo apt-get update
  ```

* 安装依赖程序

  ```bash
  sudo apt-get install make gcc
  sudo apt-get install build-essential
  sudo apt-get install libncurses5-dev
  ```

* 内核配置

  ```bash
  # 开启CONFIG_DEBUG_INFO 选项
  make menuconfig
  ```

* 编译

  ```bash
  make
  ```


## 制作磁盘镜像

### **TODO：启动的启动不起来。**





## 附录

### ubuntu5.10源配置

```
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-security main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-updates main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-proposed main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-backports main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-security main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-updates main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-proposed main restricted universe multiverse
deb-src http://mirrors.ustc.edu.cn/ubuntu-old-releases/ubuntu/ breezy-backports main restricted universe multiverse
```

### 常用命令

```bash
# 文件传输(宿主机执行命令)
scp -o KexAlgorithms=diffie-hellman-group1-sha1 source.list yuchao@192.168.179.129:~/
```

### 参考资料

* [老版ubuntu镜像下载地址](https://old-releases.ubuntu.com/releases/)
* [国内老版本ubuntu更新http://mirrors.ustc.edu.cn/ubuntu-old-releases以及sources.list的配置方法](https://blog.csdn.net/snaking616/article/details/52966634)
