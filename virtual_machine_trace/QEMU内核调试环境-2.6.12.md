



### 安装SSH

* 添加`iso`文件到虚拟机

* 安装`openssh`

  ```bash
  sudo mount /dev/hdb /mnt
  cd /mnt
  sudo dpkg -i pool/main/o/openssh/openssh-server.deb
  ```

* 访问`ssh`

  ```bash
  zssh -o KexAlgorithms=diffie-hellman-group1-sha1 -o HostKeyAlgorithms=+ssh-rsa -o PubkeyAcceptedAlgorithms=+ssh-rsa rivsidn@192.168.122.236
  ```



### 重新编译内核

```bash
sudo make modules_install
sudo make install

sudo update-initramfs -c -k "2.6.12-debug"
sudo update-grub

# 需要手动指定使用的initrd.img

```



















