仅仅大概的介绍`ftrace`　实现，不设计具体代码。

具体的代码可能涉及汇编，不同架构的实现也可能不同。



## ftrace实现

`ftrace` 只能追踪函数的入口。

`ftrace` 是基于`gcc` 的　-pg 选项，写一个简单的示例。

C代码：

```c
void func()
{
	return;
}

int main()
{
	func();

	return 0;
}
```

生成汇编代码：

```bash
gcc -S -pg func.c
```

生成的汇编代码：

```assembly
func:
	pushq	%rbp
	movq	%rsp, %rbp
1:	call	*mcount@GOTPCREL(%rip)
	nop
	popq	%rbp
	ret
main:
	pushq	%rbp
	movq	%rsp, %rbp
1:	call	*mcount@GOTPCREL(%rip)
	movl	$0, %eax
	call	func
	movl	$0, %eax
	popq	%rbp
	ret
```

如上所示，在函数调用的起始位置都会插入一个call 指令，跳转到指定位置执行一个一个函数，我们称这个函数为`mcount` 函数。

修改`mcount` 位置的代码就可以实习在函数入口处执行跟踪的目的。



## function graph 实现

`function grapth`　不仅能追踪函数入口，还能追踪函数退出。

`function grapth` 同样也是依赖于`gcc`  的　`-pg` 选项，与`ftrace` 不同的是，在进入到`mcount` 处理函数的时候，会修改函数的返回地址，当函数返回时，进入到我们准备的函数中执行，由此达到追踪函数退出的目的。



以上边的代码为例。

`main()` 调用了`func()` 函数，当`func()`进入到`mcount()` 函数时，在`mcount()` 函数中将`func()`返回的地址修改成我们自己的函数，当`func()` return 的时候不会直接返回到`main()`，而是返回到我们定义的trace 函数中执行。



## 动态ftrace 实现

动态`ftrace` 自动将`call` 指令替换成　`nop`，并将修改的函数搜集起来，整理到一个表中，没有使能的时候，默认就执行一个`nop`指令，能够有效的降低性能损耗。

