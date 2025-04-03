


| 内核     | Ubuntu版本 | busybox版本 | 对应文件 |
| ---    | ---      | ---       | ---  |
| 2.6.12 | 5.10     | TODO      |



## Ubuntu5.10内核调试

### 安装源

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

### 其他

#### 文件传输

```bash
  # 文件传输(宿主机执行命令)
  scp -o KexAlgorithms=diffie-hellman-group1-sha1 source.list yuchao@192.168.179.129:~/
```






## 附录

### Ubuntu版本内核对应

| Ubuntu版本 | 代号            | 内核版本号 |
| ---------- | --------------- | ---------- |
| 23.10      | Mantic Minotaur | 6.5        |
| 23.04      | Lunar Lobster   | 6.2        |
| 22.10      | Kinetic Kudu    | 5.19       |
| 22.04      | Jammy Jellyfish	 | 5.15	    |
| 21.10      | Impish Indri	 | 5.13     |
| 21.04      | Hirsute Hippo	 | 5.11     |
| 20.10      | Groovy Gorilla	 | 5.8      |
| 20.04      | Focal Fossa	 | 5.4      |
| 19.10      | Eoan Ermine	 | 5.3      |
| 19.04      | Disco Dingo	 | 5.0      |
| 18.10      | Cosmic Cuttlefish | 4.18     |
| 18.04      | Bionic Beaver	 | 4.15     |
| 17.10      | Artful Aardvark	 | 4.13     |
| 17.04      | Zesty Zapus	 | 4.10     |
| 16.10      | Yakkety Yak	 | 4.8      |
| 16.04      | Xenial Xerus	 | 4.4      |
| 15.10      | Wily Werewolf	 | 4.2      |
| 15.04      | Vivid Vervet	 | 3.19     |
| 14.10      | Utopic Unicorn	 | 3.16     |
| 14.04      | Trusty Tahr	 | 3.13     |
| 13.10      | Saucy Salamander	 | 3.11     |
| 13.04      | Raring Ringtail	 | 3.8      |
| 12.10      | Quantal Quetzal	 | 3.5      |
| 12.04      | Precise Pangolin	 | 3.2+     |
| 11.10      | Oneiric Ocelot	 | 3.0      |
| 11.04      | Natty Narwhal	 | 2.6.38   |
| 10.10      | Maverick Meerkat	 | 2.6.35   |
| 10.04      | Lucid Lynx	 | 2.6.32   |
| 09.10      | Karmic Koala	 | 2.6.31   |
| 09.04      | Jaunty Jackalope	 | 2.6.28   |
| 08.10      | Intrepid Ibex	 | 2.6.27   |
| 08.04      | Hardy Heron	 | 2.6.24   |
| 07.10      | Gutsy Gibbon	 | 2.6.22   |
| 07.04      | Feisty Fawn	 | 2.6.20   |
| 06.10      | Edgy Eft		 | 2.6.17   |
| 06.06      | Dapper Drake	 | 2.6.15   |
| 05.10      | Breezy Badger	 | 2.6.12   |
| 05.04      | Hoary Hedgehog	 | 2.6.10   |
| 04.10      | Warty Warthog	 | 2.6.8    |

**下载地址:**

* [Old Ubuntu Releases](https://old-releases.ubuntu.com/releases/)



### 参考资料

* [List of Ubuntu Versions with Corresponding Linux Kernel Version](https://askubuntu.com/questions/517136/list-of-ubuntu-versions-with-corresponding-linux-kernel-version)
