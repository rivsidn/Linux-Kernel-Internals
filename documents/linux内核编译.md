
## 内核编译

```bash
sudo apt-get install make 
sudo apt-get install gcc 
sudo apt-get install flex
sudo apt-get install bison
sudo apt-get install libncurses5-dev libncursesw5-dev
sudo apt-get install libssl-dev


make

make modules_install

make install
```

## 内核安装

```bash

```



## 附录

### 编译生成预处理文件

```bash
make ./net/core/dev.i
```

生成对应.c 的预处理文件。

