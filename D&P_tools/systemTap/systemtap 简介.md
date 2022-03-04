## 简介

systemTap 是一个框架，可以用来搜集运行中Linux系统的信息，分析性能或功能问题。没有systemTap时，想要搜集信息，需要重新编译、安装、重启，一系列过程，通过systemtap 不需要重新编译，通过简单的命令行接口和脚本就可以实现系统的监控。

systemtap第一个版本发布于`2005-08-04 ` ，截止到当前，最新版本`4.3`发布于`2020-06-11`。



systemtap 的核心思想是**事件**，给每一个事件分配一个**处理函数**，每当**事件**发生时，会转而执行事件分配的**处理函数**，执行完之后再返回原程序继续执行。**事件** 可以是函数运行或退出，定时器超时，systemtap 会话开启或关闭等。



## 安装

ubuntu 发行版安装

```bash
# 添加dbg apt 源
echo "deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse" | \
sudo tee -a /etc/apt/sources.list.d/ddebs.list

# 安装依赖
sudo apt-get update
sudo apt-get install linux-headers-<kernel_release>
sudo apt-get install linux-image-<kernel_release>-dbgsym

# 安装systemtap
sudo apt-get install systemtap
```



## 应用举例

### 冒烟测试

```bash
$ cat hello-world.stp
probe begin
{
	print("hello wordl\n")
	exit()
}
$ stap hello-world.stp
hello world
```

`begin` 意思是在脚本启动时运行，`exit()` 是退出本次监控，如果没有调用 `exit()` 需要手动 ctrl+c。

执行该脚本就简单的输出一个 `hello world`，然后退出。



### 监控系统调用

```bash
$ cat strace-open.stp
probe syscall.open
{
	printf ("%s(%d) open (%s)\n", execname(), pid(), argstr)
}
probe timer.ms(4000)
{
	exit()
}
```

监控 `open` 系统调用，4000ms 之后调用 `exit()` 函数退出本次监控。



### 监控函数

```bash
$ cat trace-func.stp 
# 监控内核全局函数
probe kernel.function("vfs_write")
	  kernel.function("vfs_read")
{
	printf("%s(%d) %s", execname(), pid(), ppfunc())
}
# 监控内核静态函数
probe kernel.function("___sys_recvmsg@net/socket.c").call
{
	printf("%s -> %s\n", thread_indent(1), ppfunc())
}
probe kernel.function("___sys_recvmsg@net/socket.c").return
{
	printf("%s <- %s\n", thread_indent(-1), ppfunc())
}
# 监控模块函数
probe module("r8169").function("rtl8169_poll").call
{
	printf("%s call...\n", ppfunc())
}
probe module("r8169").function("rtl8169_poll").return
{
	printf("%s return...\n", ppfunc())
}

# 监控10s退出
probe timer.ms(10000)
{
	exit()
}
```

`ppfunc()` 用于打印出函数名称。



### 监控收包

```bash
probe kernel.function("ip_rcv")
{
	iphdr = __get_skb_iphdr($skb)
	saddr = format_ipaddr(__ip_skb_saddr(iphdr), @const("AF_INET"))
	daddr = format_ipaddr(__ip_skb_daddr(iphdr), @const("AF_INET"))

	printf("%15s - %15s\n", saddr, daddr)
}
probe timer.ms(4000)
{
	exit()
}
```

打印出收到的包 IPv4 地址。



### 监控netfilter示例

```bash
#! /usr/bin/env stap

global packets

probe begin {
      print ("Collecting data... Type Ctrl-C to exit and display results.")
}

probe netfilter.ipv4.pre_routing {
      // Using aggregates avoids contention from packets being sent in
      // parallel from different processors:
      packets[saddr, daddr] <<< length
}

probe end {
      print ("\n")
      foreach ([saddr, daddr] in packets-) {
              printf ("%15s --> %15s : %d packets, %d total bytes\n",
                      saddr, daddr,
                      @count(packets[saddr,daddr]), @sum(packets[saddr,daddr]))
      }
}

probe timer.ms(4000)
{
	exit()
}
```

目测应该是统计`netfilter ipv4 pre` 接收到的源地址、目的地址报文的报文数和报文长度，4000ms之后结束。





## 实现原理

[Architecture of systemtap :a Linux trace/probe tool](https://sourceware.org/systemtap/archpaper.pdf)



## 附录

[systemtap官网资料](https://sourceware.org/systemtap/documentation.html)



