```
u switch-mode

b 0x900ce		# 下一条执行 jmpf 0x9020:0000 ，也就是跳转到 setup.S 中执行

b 0x9071a		# loader_ok 标号处

b 0x90724		# meme820 标号处

b 0x90740		# jmpe820 中int 0x15 后一条指令

b 0x907df		# is_disk1 标号



```





```asm
loader_ok:
# Get memory size (extended mem, kB)

	xorl	%eax, %eax
	movl	%eax, (0x1e0)			# 此处对应bootsect.S 中的msg1 最后四个字节，也就是ing\0
	
	
	
	
```



```asm
#define E820MAP	0x2d0		/* our map */
#define E820MAX	32			/* number of entries in E820MAP */
#define E820NR	0x1e8		/* # entries in E820MAP */

meme820:
	xorl	%ebx, %ebx				# 清空，首先从0 开始
	movw	$E820MAP, %di			# 映射数据起始位置 0x9000:0x02d0

jmpe820:
	movl	$0x0000e820, %eax		# 获取系统内存映射
	movl	$SMAP, %edx				# 设置参数
	movl	$20, %ecx				# 存储结果的缓存大小
	pushw	%ds						# 压栈 ds
	popw	%es						# 将ds 的值赋值给es
	int	$0x15						# 调用中断，如果失败设置cf
	jc	bail820						# 失败则跳转

	cmpl	$SMAP, %eax				# 失败则跳转
	jne	bail820

good820:
	movb	(E820NR), %al			# 获取当前存储的表项条目数
	cmpb	$E820MAX, %al			# 比较最大条目数、当前条目数
	jnl	bail820						# 如果当前条目数大于等于最大条目数则跳转

	incb	(E820NR)				# 递增条目数 0x9000:0x01e8
	movw	%di, %ax
	addw	$20, %ax
	movw	%ax, %di				# di 增加20 字节
again820:
	cmpl	$0, %ebx				# 测试是否结束
	jne	jmpe820						# 没结束则跳转
bail820:
```



```asm
meme801:
	movw	$0xe801, %ax			# 设置中断参数
	int		$0x15					# 调用中断
	jc		mem88

	andl	$0xffff, %edx			
	shll	$6, %edx     			# 此时edx 中内存是以64k 为单位，乘64 之后以1k 为单位
	movl	%edx, (0x1e0)
	andl	$0xffff, %ecx			# 获取内存大小
	addl	%ecx, (0x1e0)			# 将内存大小存储到 0x9000:0x01e0 
```









## 参考资料

* [BIOS中断查询](#http://www.ctyme.com/intr/int.html)
* 

