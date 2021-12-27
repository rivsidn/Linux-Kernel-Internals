```
b 0x900ce
c
# 下一条执行 jmpf 0x9020:0000 ，也就是跳转到 setup.S 中执行

u switch-mode

trace on

set u off

b 0x90634

b 0x90636

b 0x9071a		# loader_ok 标号处

b 0x90724		# meme820 标号处

```





```asm
loader_ok:
# Get memory size (extended mem, kB)

	xorl	%eax, %eax
	movl	%eax, (0x1e0)			# 此处对应bootsect.S 中的msg1 最后四个字节，也就是ing\0
	
	
	
	
```



```asm
meme820:
	xorl	%ebx, %ebx				# 清空，首先从0 开始
	movw	$E820MAP, %di			

jmpe820:
	movl	$0x0000e820, %eax		# 获取系统内存映射
	movl	$SMAP, %edx				# 设置参数
	movl	$20, %ecx				# 存储结果的缓存大小
	pushw	%ds						# 压栈 ds
	popw	%es						# 将ds 的值赋值给es
	int	$0x15						
	jc	bail820				

	cmpl	$SMAP, %eax
	jne	bail820
```







## 参考资料

* [BIOS中断查询](#http://www.ctyme.com/intr/int.html)
* 

