当前总共使用了两种启动方式：

1. 自制根文件系统，直接启动`bzImage` 文件

   ```bash
   # 指定参数分别为内核、根文件系统、启动参数
   qemu-system-x86_64 -kernel bzImage -initrd initrd.img -append "nokaslr root=/dev/ram init=/bin/sh console=ttyS0 nmi_watchdog=0" -nographic
   
   ```

2. 直接启动`img`文件

   ```bash
   # 指定启动镜像，内存
   qemu-system-x86_64 xxx.img -m 4g -nographic
   
   ```
   
   






