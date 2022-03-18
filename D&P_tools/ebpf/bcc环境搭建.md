## 软件包安装

### 安装

```bash
sudo apt-get install bpfcc-tools linux-headers-$(uname -r)
sudo apt-get install python3-bpfcc
```

**Tips： 参照官方install文档安装之后只能以python2 执行，需要单独安装python3-bpfcc 程序。**

### 卸载

```bash
sudo apt-get autoremove bpfcc-tools python3-bpfcc
```



**Tips： 直接安装的18.04 上有的用例跑不过，升级系统版本到20.04 之后，源码编译安装。**



## 源码安装

基于`ubuntu 20.04`。

### 安装

```bash
# 20.04 安装依赖文件
sudo apt install -y bison build-essential cmake flex git libedit-dev libllvm7 llvm-7-dev libclang-7-dev python zlib1g-dev libelf-dev libfl-dev python3-distutils
```

安装脚本

```bash
git clone https://github.com/iovisor/bcc.git
# 原有基础上切换到 0.24.0 版本，否则编译不过去
cd bcc && git checkout v0.24.0 && cd ..
mkdir bcc/build; cd bcc/build
cmake ..
make
sudo make install
cmake -DPYTHON_CMD=python3 .. # build python3 binding
pushd src/python/
make
sudo make install
popd
```

**异常问题**

* error: no matching function for call to ‘llvm::object::SectionRef::getName() const’

  参考资料，[BCC does not support LLVLM 7 or earlier anymore with the master branch](https://github.com/iovisor/bcc/issues/3881)

### 卸载

**TODO：暂略。**



## 冒烟测试

### hello world代码

```python
#!/usr/bin/python
# Copyright (c) PLUMgrid, Inc.
# Licensed under the Apache License, Version 2.0 (the "License")

# run in project examples directory with:
# sudo ./hello_world.py"
# see trace_fields.py for a longer example

from bcc import BPF

# This may not work for 4.17 on x64, you need replace kprobe__sys_clone with kprobe____x64_sys_clone
BPF(text='int kprobe__sys_clone(void *ctx) { bpf_trace_printk("Hello, World!\\n"); return 0; }').trace_print()
```

### 程序运行

```bash
$ sudo python2 hello_world.py 
  gsd-media-keys-3071    [002] .... 17271.685602: 0: Hello, World!
  gsd-media-keys-22596   [003] .... 17271.686959: 0: Hello, World!
  gsd-media-keys-3071    [000] .... 17271.690932: 0: Hello, World!
$ sudo python hello_world.py 
          chrome-6833    [002] .... 17280.284978: 0: Hello, World!
 ThreadPoolForeg-10676   [002] .... 17280.285394: 0: Hello, World!
  gsd-media-keys-3071    [000] .... 17280.545000: 0: Hello, World!
  gsd-media-keys-22619   [003] .... 17280.546424: 0: Hello, World!
```



## 参考资料

* [Installing BCC](https://github.com/iovisor/bcc/blob/master/INSTALL.md)
* [hello_world.py](https://github.com/iovisor/bcc/blob/master/examples/hello_world.py)

