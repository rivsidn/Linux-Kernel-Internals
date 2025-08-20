
制作docker 镜像，以 `ubuntu 5.10` 为例说明.

## 制作基础根文件系统

```bash
# 工具安装(已安装则忽略)
sudo apt-get update
sudo apt-get install debootstrap
# 生成根文件系统
sudo debootstrap --arch=i386 breezy ubuntu-5.10-rootfs http://old-releases.ubuntu.com/ubuntu/

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
docker run -it -v /home/yuchao/kernel/linux_stable/.git/workspace/Linux-2.6.12:/root ubuntu-5.10
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



