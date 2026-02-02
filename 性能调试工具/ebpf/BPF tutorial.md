# 安装

```bash
sudo apt-get install bpftrace
```

#  基础

## 程序注释

`bpftrace` 注释方式和`c`语言方式一样，分为单行注释，多行注释。

```c
//但行注释

/*
 * 多行注释
 */
```

## 代码执行

代码执行与其他脚本一致，分两种方式，单行程序执行、文件执行。

```bash
sudo bpftrace -e 'BEGIN{printf("hello world!\n");}'
```



```c
#!/usr/local/bin/bpftrace

BEGIN
{
    printf("hello world!\n");
}
```

# 语法

## 变量

### 内置变量

由`bpftrace`自己定义的变量，可以直接读取信息。

### 临时变量

用于临时存储数据、计算的变量，以'$' 作为前缀。

### 映射变量

以'@' 作为前缀，使用映射表存储数据，可以用于全局存储，在不同语句间传递信息。

## 探针

```bash
# bpftrace -l 可以查看内核级别的探针类型
探针类新：标识符1：标识符2：...
```

探针支持通配符。



## 过滤器

过滤器是一个布尔表达式，只有当检查内容为真时才会继续执行后面的程序。

```bash
/pid/

/pid == 100 || pid == 1234/
```



## 代码块

```bash
探针
{
	语句1；
	语句2；
	语句3；
}
```



## 函数

详细信息可以参考：

`https://github.com/iovisor/bpftrace/blob/master/docs/reference_guide.md`











# 示例

## 获取vfs_read 调用时间

```bash
#!/usr/local/bin/bpftrace

kprobe:vfs_read
{
	@start[pid] = nsecs;
}

kretprobe:vfs_read
/@stard[pid]/
{
	@ns[comm] = hist(nsecs - @start[pid]);
	delete(@start[pid])
}
```





# 附录

## 参考资料

* []()