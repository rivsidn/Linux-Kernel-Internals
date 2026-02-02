通过UDP 报文将设备的日志信息发送到目标机器上显示。

`netconsole` 可以编译到内核中，也可以编译成模块，编译到内核中时需要通过启动参数指定目标机，编译成模块可以通过在模块加载的时候可以在模块加载的时候指定目标机，两种方式都可以在使能`CONFIG_NETCONSOLE_DYNAMIC` 后，动态的添加目标机。

我们此处仅关注将`netconsole` 编译成模块，在模块加载时指定参数目标机的方式，其他详细使用说明可以参考内核文档(Documentation/networking/netconsole.txt)。



## 内核编译

使能`CONFIG_NETCONSOLE` 选项。



## 模块加载

```bash
modprobe netconsole netconsole=@172.31.3.139/eth4,@172.31.3.136/
```

* 默认的源端口号为 6665，默认的目的端口号为 6666
* 没指定目的mac的时候将使用广播mac地址



## 目标机消息获取

```bash
netcat -l -p 6666 -u
```



## 注意

只有输出到控制台的消息才能发送到目标机，如果目标机获取不到想要的消息，可能需要设置`/proc/sys/kernel/printk` 。



## 附录

* 用户态输出消息到dmesg

  ```bash
  echo "dmesg output..." > /dev/kmsg
  ```

* 

