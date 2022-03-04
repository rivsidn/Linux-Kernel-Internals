* [查看函数参数](#查看函数参数)
* [查看结构体成员](#查看结构体成员)
* [查看函数返回值](#查看函数返回值)
* [追踪函数执行流程](#追踪函数执行流程)
* [查看局部变量](#查看局部变量)



## 查看函数参数

以为 `ip_rcv` 为例。

### 反汇编查看函数参数寄存器

```c
int ip_rcv(int *a, int *b, int *c, int *d)
{
	*a = 0;
}
int main()
{
	int a, b, c, d;
	a = 1;
	b = 2;
	c = 3;
	d = 4;

    ip_rcv(&a, &b, &c, &d);
	
    printf("%d %d %d %d\n", a, b, c, d);
	return 0;
}
```

````asm
ip_rcv:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)		#rdi 第一个参数
	movq	%rsi, -16(%rbp)		#rsi 第二个参数
	movq	%rdx, -24(%rbp)		#rdx 第三个参数
	movq	%rcx, -32(%rbp)		#rcx 第四个参数
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	nop
	popq	%rbp
	ret
main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -24(%rbp)
	movl	$2, -20(%rbp)
	movl	$3, -16(%rbp)
	movl	$4, -12(%rbp)
	leaq	-12(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	leaq	-20(%rbp), %rsi
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ip_rcv
	movl	-12(%rbp), %esi
	movl	-16(%rbp), %ecx
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	movl	%esi, %r8d
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdi
	xorq	%fs:40, %rdi
	je	.L4
	call	__stack_chk_fail@PLT
	leave
	ret
````

### 查看函数参数传递寄存器

| 寄存器 | 参数       |
| ------ | ---------- |
| rdi    | 第一个参数 |
| rsi    | 第二个参数 |
| rdx    | 第三个参数 |
| rcx    | 第四个参数 |

### KDB中查看寄存器内容

```
[0]kdb> rd
CPU 0 <d>Modules linked in: xt_mark ip_set_hash_net ip_set nfnetlink nf_nat_sip nf_conntrack_sip nf_nat_mms nf_conntrack_mms nf_nat_ir]
<c>
<d>Pid: 3039, comm: bash Not tainted 2.6.35.6 #125 MAHOBAY/To be filled by O.E.M.
<d>RIP: 0010:[<ffffffff8132d290>]  [<ffffffff8132d290>] ip_rcv+0x0/0x560
<d>RSP: 0018:ffff880002403c88  EFLAGS: 00000282
<d>RAX: ffffffff816f49a0 RBX: ffff8801004f56c0 RCX: ffff88005133c000
<d>RDX: ffffffff816f6340 RSI: ffff88005133c000 RDI: ffff8801004f56c0
<d>RBP: ffff880002403ce0 R08: 0000000000000008 R09: ffffffff816f49a0
<d>R10: ffff88005133c000 R11: 0000000000000001 R12: ffffffff816f4960
<d>R13: ffffffff816f6340 R14: ffff88005133c000 R15: 0000000000000000
<d>FS:  00007f696dfde720(0000) GS:ffff880002400000(0000) knlGS:0000000000000000
<d>CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
<d>CR2: 00007f696e7b3000 CR3: 0000000044f4f000 CR4: 00000000000406b0
<d>DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
<d>DR3: 0000000000000000 DR6: 00000000ffff4ff0 DR7: 0000000000000400
Process bash (pid: 3039, threadinfo ffff88007879e000, task ffff88004457d210)
```

如上图所示，第二个参数和第四个参数，`RSI` 和 `RCX` 中内容是相同的.



## 查看结构体成员

示例，接上。

### 查看结构体成员偏移量

```c
yuchao@yuchao:~/workspace/blade/main_longtime/platform/kernel.x86_64$ gdb vmlinux 
Reading symbols from vmlinux...done.
(gdb) p &((struct net_device*)0)->name
$1 = (char (*)[16]) 0x0 <irq_stack_union>
(gdb)
yuchao@yuchao:~/workspace/blade/main_longtime/platform/kernel.x86_64$ gdb vmlinux 
Reading symbols from vmlinux...done.
(gdb) p &((struct sk_buff*)0)->head
$1 = (unsigned char **) 0xe8 <irq_stack_union+232>
(gdb) p &((struct sk_buff*)0)->network_header
$2 = (sk_buff_data_t *) 0xd4 <irq_stack_union+212>
(gdb) 
```

### 查看结构体内容

* 查看网卡名称

  ```
  [0]kdb> mds 0xffff88005133c000
  0xffff88005133c000 6d75640034687465   eth4.dum
  0xffff88005133c008 0000000000782e79   y.x.....
  0xffff88005133c010 ffff880044d16860   `h.D....
  0xffff88005133c018 0000000000000000   ........
  0xffff88005133c020 ffff8801005dbe38   8.].....
  0xffff88005133c028 0000000000000000   ........
  0xffff88005133c030 00000000f7d20000   ........
  0xffff88005133c038 00000000f7d00000   ........
  ```

* 查看报文数据

  ```
  [0]kdb> mdr 0xFFFF8801004F57A8 8	#skb->head(0xffff8801004f56c0+0xe8)
  002cb5440088ffff
  [0]kdb> mdr 0xFFFF8801004F5794 4	#skb->network_header(0xffff8801004f56c0+0xd4)
  4e000000
  [0]kdb> mds 0xffff880044b52c4e  	#skb->head+skb->newwork_header
  0xffff880044b52c48 004500085db7a3c6   ...]..E.
  0xffff880044b52c50 1180000034514e00   .NQ4....
  0xffff880044b52c58 140a461e140afe97   .....F..
  0xffff880044b52c60 3a0089008900ff1e   .......:
  0xffff880044b52c68 01001001ddf5a519   ........
  0xffff880044b52c70 4520000000000000   ...... E
  0xffff880044b52c78 454f434646454542   BEEFFCOE
  0xffff880044b52c80 46504547454e4348   HCNEGEPF
  ```
  
  

## 查看函数返回值

示例，接上。

函数可以通过两种方式来返回：

1. 指针参数
2. 返回值`return`

```c
  1 func:                                               \  1 #include <stdio.h>
  2         pushq   %rbp                                \  2 
  3         movq    %rsp, %rbp                          \  3 int func(int a)
  4         movl    %edi, -4(%rbp)                      \  4 {                                                   
  5         cmpl    $0, -4(%rbp)                        \  5         if (a) {
  6         je      .L2                                 \  6                 return 0;
  7         movl    $0, %eax                            \  7         } else {
  8         jmp     .L3                                 \  8                 return 1;
  9 .L2:                                                \  9         }
 10         movl    $1, %eax                            \ 10 }
 11 .L3:                                                \ 11 
 12         popq    %rbp                                \ 12 int main()
 13         ret                                         \ 13 {
 14 .LC0:                                               \ 14         int ret;
 15         .string "%d\n"                              \ 15         int a = 10;
 16 main:                                               \ 16 
 17         pushq   %rbp                                \ 17         ret = func(a);
 18         movq    %rsp, %rbp                          \ 18         printf("%d\n", ret);
 19         subq    $16, %rsp                           \ 19 
 20         movl    $10, -8(%rbp)                       \ 20         return 0;
 21         movl    -8(%rbp), %eax                      \ 21 }
 22         movl    %eax, %edi                          \~                                                       
 23         call    func                                \~                                                       
 24         movl    %eax, -4(%rbp)                      \~                                                       
 25         movl    -4(%rbp), %eax                      \~                                                       
 26         movl    %eax, %esi                          \~                                                       
 27         leaq    .LC0(%rip), %rdi                    \~                                                       
 28         movl    $0, %eax                            \~                                                       
 29         call    printf@PLT                          \~                                                       
 30         movl    $0, %eax                            \~                                                       
 31         leave                                       \~                                                       
 32         ret                                         \~                                                       
~                                                       \~                                                       
~                                                       \~                                                       
```

如上所示，函数的返回值在寄存器`eax` 中。

### 返回值 return

函数调用过程中会在栈上存储返回地址，在返回地址处加断点，函数返回之后，获取返回值。

```
[0]kdb> mds 0xffff880002403c88
0xffff880002403c88 ffffffff81301bca __netif_receive_skb+0x36a  
0xffff880002403c90 ffff880002403cc0   .<@.....
0xffff880002403c98 ffffffff8105ed00 getnstimeofday+0x60  
0xffff880002403ca0 ffff8801004f56c0   .VO.....
0xffff880002403ca8 0000000000000003   ........
0xffff880002403cb0 ffff88005133c710   ..3Q....
0xffff880002403cb8 0000000000000003   ........
0xffff880002403cc0 ffff88005133c710   ..3Q....
[0]kdb> bp 0xffffffff81301bca
Instruction(i) BP #1 at 0xffffffff81301bca (__netif_receive_skb+0x36a)
    is enabled  addr at ffffffff81301bca, hardtype=0 installed=0
[0]kdb> bl
Instruction(i) BP #0 at 0xffffffff8132d290 (ip_rcv)
    is enabled  addr at ffffffff8132d290, hardtype=0 installed=0
Instruction(i) BP #1 at 0xffffffff81301bca (__netif_receive_skb+0x36a)
    is enabled  addr at ffffffff81301bca, hardtype=0 installed=0
[0]kdb> go
Entering kdb (current=0xffff88004457d210, pid 3039) on processor 0 due to Breakpoint @ 0xffffffff81301bca
[0]kdb> rd
CPU 0 <d>Modules linked in: xt_mark ip_set_hash_net ip_set nfnetlink nf_nat_sip nf_conntrack_sip nf_nat_mms nf_c]
<c>
<d>Pid: 3039, comm: bash Not tainted 2.6.35.6 #125 MAHOBAY/To be filled by O.E.M.
<d>RIP: 0010:[<ffffffff81301bca>]  [<ffffffff81301bca>] __netif_receive_skb+0x36a/0x680
<d>RSP: 0018:ffff880002403c90  EFLAGS: 00000282
<d>RAX: 0000000000000000 RBX: ffff8801004f56c0 RCX: ffff8801004f4c40
<d>RDX: 0000000000000000 RSI: ffff8801004f56c0 RDI: ffff8801004f56c0
<d>RBP: ffff880002403ce0 R08: 0000000000000000 R09: 0000000000000001
<d>R10: 0000000000000000 R11: 0000000000000000 R12: ffffffff816f4960
<d>R13: ffffffff816f6340 R14: ffff88005133c000 R15: 0000000000000000
<d>FS:  00007f696dfde720(0000) GS:ffff880002400000(0000) knlGS:0000000000000000
<d>CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
<d>CR2: 00007f696e7b3000 CR3: 0000000044f4f000 CR4: 00000000000406b0
<d>DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
<d>DR3: 0000000000000000 DR6: 00000000ffff4ff0 DR7: 0000000000000400
```

如上所示，此时`RAX`寄存器的值为 0，此时函数的返回值为 0。

### 指针参数

函数调用的时候，记录参数(也就是指针值)，在函数返回IP处加断点，断住之后，通过获取结构体成员的方式获取结构体数据。



## 追踪函数执行流程

连接`KDB`，`KDB` 中查看函数调用流程。

```
# kdb 中执行
[0]kdb> kgdb

# PC 中执行
$ sudo gdb vmlinux 
Reading symbols from vmlinux...done.
(gdb) set serial baud 115200
(gdb) target remote /dev/ttyUSB0
Remote debugging using /dev/ttyUSB0
(gdb) n
424		pm_time_stamp();
(gdb) 
420	{
(gdb) 
424		pm_time_stamp();
(gdb) 
428		if (skb->pkt_type == PACKET_OTHERHOST)
(gdb) 
432		IP_UPD_PO_STATS_BH(dev_net(dev), IPSTATS_MIB_IN, skb->len);
(gdb) 
```



**注意：KDB或者是KGDB都无法调试 `schedule` 函数。**



## 查看局部变量

`KDB` 中查看局部变量。

```
(gdb) info locals
```





