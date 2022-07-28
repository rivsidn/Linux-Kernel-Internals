通过宿主机访问磁盘，可以通过`git`将文件克隆到虚拟磁盘中，挂载虚拟机编译之后，`fetch`到本地来比较。



```bash
# 准备工作，安装软件依赖
$ sudo apt-get install libaio1 libaio-dev

# 查看虚拟磁盘分区信息
$ sudo vmware-mount -p <file>.vmdk

# 挂载特定分区到某一目录
$ sudo vmware-mount <file>.vmdk 1 /mnt/1

# 卸载已挂载的分析
$ sudo vmware-mount -d /mnt/1
```



## 附录

### 参考资料

* [如何直接访问vmware vmdk文件中的内容](https://www.ai2news.com/blog/171284/)

