```
b 0x7c00
c

# 切换汇编格式
u switch-mode

# 关闭自动反汇编，因为此时反汇编的是下一条需要执行的指令
set u off

# 开启追踪，输出执行结束的指令
trace on

# load_setup 之前的打印输出
<bochs:48> xp /6xh 0xfefde
[bochs]:
0x000fefde <bogus+       0>:	0x02af	0x0225	0x1b12	0x6cff	0x0ff6	0x4f08
<bochs:49> xp /6xh 0x93ff4
[bochs]:
0x00093ff4 <bogus+       0>:	0x02af	0x0225	0x1b24	0x6cff	0x0ff6	0x4f08
<bochs:50> xp /2xh 0x0078
[bochs]:
0x00000078 <bogus+       0>:	0x3ff4	0x9000

```



```asm
_start:
	# 将自身移动到INITSEG 位置，跳转到go 执行
	movw	$BOOTSEG, %ax
	movw	%ax, %ds
	movw	$INITSEG, %ax
	movw	%ax, %es
	movw	$256, %cx
	subw	%si, %si
	subw	%di, %di
	cld
	rep
	movsw
	ljmp	$INITSEG, $go

	# 1.设置栈寄存器，预留了12 字节空间
	# 2.读取0x0000:0x0078 中内容0xf000:0xefde 到ds:si 中
	# 3.读取ds:si[0xf000:0xefde]中12 字节内容到0x9000:0x3ff4 中，也就是上边预留的栈顶12 字节空间
	# 4.修改0x9000:0x3ff4 中读取到内容
	# 5.修改0x0000:0x0078 指向的内容
	# 综上所述，0x0000:0x0078 中内容保存的是一个地址，地址指向特定的内容，将该部分内容读取出来之后并修改，
	# 并修改0x0000:0x0078 中保存的地址为修改后内容的地址
	# 0x0000:0x0078 中保存的是磁盘参数表地址，读取磁盘参数表，修改磁盘参数表内容，修改0x0000:0x0078 中
	# 保存的地址.
go:	movw	$0x4000-12, %di
	movw	%ax, %ds
	movw	%ax, %ss
	movw	%di, %sp

	movw	%cx, %fs		# 设置fs 0x0000
	movw	$0x78, %bx		# 设置bx 0x0078
	pushw	%ds				# 压栈ds 0x9000
	ldsw	%fs:(%bx), %si	# 读取fs:bx 指向内容0xf000:0xefde 到ds:si 寄存器
	movb	$6, %cl
	pushw	%di				# 压栈di 0x4000-12=0x3ff4
	rep
	movsw					# ds:si[0xf000:0xefde] 指向内容移动到es:di[0x9000:0x3ff4] 指向地址
	popw	%di				# 恢复di 0x4000-12=0x3ff4
	popw	%ds				# 恢复ds 0x9000
	movb	$36, 0x4(%di)	# 修改ds:(di+4)[0x9000:0x3ff8] 指向内容为 0x24
	movw	%di, %fs:(%bx)	# di 寄存器内容0x3ff4 保存到fs:bx 指向地址
	movw	%es, %fs:2(%bx)	# es 寄存器内容0x9000 保存到fs:(bx+2) 指向地址

```





```asm
	# 1.重设软盘控制器
	# 2.读取5 个扇区，将扇区中内容写到0x9000:0x0200
load_setup:
	xorb	%ah, %ah
	xorb	%dl, %dl
	int 	$0x13	
	xorw	%dx, %dx
	movb	$0x02, %cl
	movw	$0x0200, %bx			# 读取基地址es:bx[0x9000:0x0200]
	movb	$0x02, %ah
	movb	setup_sects, %al		# 设置读取扇区数量，此时是 5
	int	$0x13
	jnc	ok_load_setup				# 查看cf，如果没有设置则跳转到ok_load_setup 执行

	pushw	%ax
	call	print_nl
	movw	%sp, %bp
	call	print_hex
	popw	%ax	
	jmp	load_setup					# 跳转到load_setup 循环执行
```



```asm
ok_load_setup:
	movw	$disksizes, %si			# 将disksizes 符号偏移量0x01d6 保存到si 寄存器中
probe_loop:
	lodsb							# 加载ds:si 指向的内容到al，si 自动加 1
	cbtw							# 拓展al 到ax
	movw	%ax, sectors
	cmpw	$disksizes+4, %si
	jae	got_sectors

	xchgw	%cx, %ax				
	xorw	%dx, %dx				# 清空 dx
	xorb	%bl, %bl				# 清空 bl
	movb	setup_sects, %bh
	incb	%bh
	shlb	%bh
	movw	$0x0201, %ax			# 服务2，第1个扇区
	int	$0x13
	jc	probe_loop
```



```
<bochs:55> reg
eax: 0x00000201 513
ecx: 0x00090024 589860
edx: 0x00000000 0
ebx: 0x00000c00 3072
esp: 0x00003ff4 16372
ebp: 0x00000000 0
esi: 0x000001d7 471
edi: 0x00003ff4 16372
eip: 0x0000007d
eflags 0x00000006: id vip vif ac vm rf nt IOPL=0 of df if tf sf zf af PF cf
```

### INT 13h AH=02h: 读取磁盘

| 寄存器 | 表示信息                 |
| ------ | ------------------------ |
| AH     | 02h                      |
| AL     | 读取的扇区数量           |
| CH     | 磁道                     |
| CL     | 扇区                     |
| DH     | 磁头                     |
| DL     | 驱动，表示从那个设备中读 |
| ES:BX  | 缓存区指针               |

**返回值**

| 寄存器 | 表示信息               |
| ------ | ---------------------- |
| CF     | 失败时非零，成功时为零 |
| AH     | 返回值                 |
| AL     | 实际读取的数量         |







## TODO

* 如何查看段寄存器的内容

  `sreg`

* 



## 参考资料

* [INT 13H](#https://en.wikipedia.org/wiki/INT_13H)
