`Fedora14` 虚拟机用于学习`linux 2.6.25.6` 内核代码，希望达到的效果是：

1. 可以通过宿主机直接访问虚拟机
2. 虚拟机可以直接编译宿主机代码



## 用户名

| 内核版本     | 镜像                   | 用户名  | 密码   |
| ------------ | ---------------------- | ------- | ------ |
| linux-2.6.35 | Fedora-14-i386-DVD.iso | rivsidn | passwd |



## 用户添加sudo权限

> On Fedora, it is the `wheel` group the user has to be added to, as this group has full admin privileges. Add a user to the group using the following command:
>
> ```
> $ sudo usermod -aG wheel username
> ```
>
> If adding the user to the group does not work immediately, you may have to edit the `/etc/sudoers` file to uncomment the line with the group name:
>
> ```
> $ sudo visudo
> ...
> %wheel ALL=(ALL) ALL
> ...
> ```
>
> **You will need to logout and back in for changes to take effect.**



## 虚拟机安装SSH

```bash
# 是否安装了SSH
rpm -qa | grep openssh-server
# 安装
yum install openssh-server

# 修改配置文件
vi /etc/ssh/sshd_config
# 重启服务
/etc/rc.d/init.d/sshd restart

# SSH服务状态
service sshd status
```



## 宿主机开启NFS

**注意：参考之前文档操作。**



## 参考资料

* [Adding a user to sudoers](https://docs.fedoraproject.org/en-US/quick-docs/adding_user_to_sudoers_file/)
* [ Configure NFS Server to share any directories.](https://www.server-world.info/en/note?os=Fedora_14&p=nfs)
* 
