## 安装

```bash
sudo apt-get install bpftrace
```



## 冒烟测试

**Tips：bpftrace 只能在root 下运行。**

```bash
$ sudo bpftrace -e 'BEGIN {printf("hello world!\n")}' 
Attaching 1 probe...
hello world!
```





## 参考资料

* [BPFtrace编程入门](https://mp.weixin.qq.com/s?__biz=MzI3NzA5MzUxNA==&mid=2664611735&idx=1&sn=4daac15114c26c89843afdf59e4c2e60&chksm=f04d9272c73a1b64bf9ca2b29aa806811c4ac74fd1819015f7e0f5b0e59ecce48ee3630e5a37&exportkey=AeCHcILlhpa8JR57MJ2pxJc%3D&acctmode=0&pass_ticket=xQMxo4zoKJDKywiEBIzGXuh8HyB0V7EEdpVjGWno1gUUPycaY%2FexmN8ibcdbKzIv&wx_header=0#rd)
* [bpftrace install](https://github.com/iovisor/bpftrace/blob/master/INSTALL.md)



