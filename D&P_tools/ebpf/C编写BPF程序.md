## 编译环境搭建

个人理解，编译C BPF程序有两种方式，一种是依赖内核代码，直接在内核代码路径下编译；另一种是依赖库，通链接库编译。

### 内核代码编译环境

```bash
# 安装内核代码
apt install linux-source
cd /usr/src
tar -jxvf linux-source-X.X.X.tar.bz2

# 安装内核编译依赖文件，由于本地之前编译过内核，所以不需要安装
# 安装Clang 和 LLVM
apt install clang llvm

# 设置config 文件
cd linux-sourece.X.X.X
cp /boot/config-X.X.X-gereric .config

# 编译前准备(可以有部分操作没有实际意义)
make menuconfig
make modules_prepare
make scripts
make headers_install

# 编译BPF程序
make M=samples/bpf
```

内核自带的程序编译通过之后就可以实现自己的示例程序了。

### 库编译环境

**TODO**



## 内核编译示例

### 代码

```c
//hello_kernel.c
#include <uapi/linux/bpf.h>
#include "bpf_helpers.h"

SEC("kprobe/sys_sync")
int bpf_prog(void *ctx)
{
    char msg[] = "hello world!\n";
    bpf_trace_printk(msg, sizeof(msg));
    return 0;
}
char _license[] SEC("license") = "GPL";
```

```c
//hello_user.c
#include "BPF_load.h"

int main(void)
{
    if (load_BPF_file(hello_kern.o))
        return -1;
    read_trace_pipe();
    return 0;
}
```

修改`Makefile` :

```makefile
# List of programs to build
hostprogs -y := hello

# LibBPF dependencies
hello-objs := BPF_load.o hello_user.o
    
#Tell kbuild to always build the programs
always += hello_kern.o
```

### 执行

```bash
# 编译
make M=samples/bpf
# 执行
./hello 
            sync-122758  [003] .... 24398.842908: 0: hello world!
```



## TODO

* 如何获取已经加载的



## 附录

###  参考资料

* [BPF C编程入门](https://mp.weixin.qq.com/s?__biz=MzI3NzA5MzUxNA==&mid=2664611713&idx=1&sn=951676066269815c7049f37144570f02&chksm=f04d9264c73a1b7240c5085bb69a87fca1ff76fdb46c8fdd3a0391327b73f736f671619ba7d4&mpshare=1&scene=1&srcid=0318XE1ubwJKxqkI9ApsiNsQ&sharer_sharetime=1647595852196&sharer_shareid=9880544caf5a40bf6ff8bc80cf8a4586&exportkey=AZy8gCP0zxSAT3CHKOHmza0%3D&acctmode=0&pass_ticket=ZPKc4lvFonNvAU0zWvU9Szy6CYWAXn07N%2BPM2oQ0bDvsnLjCnPigZYTMU0NC7apT&wx_header=0#rd)

