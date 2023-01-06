## 工具使用





## 附录

### 指令示例

#### 统计报文个数(samples/bpf/sock_example.c)

```c

BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),        					/* r6 = r1 */
BPF_LD_ABS(BPF_B, ETH_HLEN + offsetof(struct iphdr, protocol)), /* r0 = ip->proto */
BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4), 					/* *(u32 *)(fp - 4) = r0 */
BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),       					/* r2 = fp */
/* r2指向保存ip->proto的地址 */
BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4),      					/* r2 = r2 - 4 */
BPF_LD_MAP_FD(BPF_REG_1, map_fd),           					/* r1 = map_fd */
/* 查询map，参数分别为map_fd，*key(指针类型) */
BPF_CALL_FUNC(BPF_FUNC_map_lookup_elem), 						/* r0 = map_lookup(r1, r2) */
/* 如果查询失败则跳过后两条更新指令，直接退出 */
BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2), 							/* if (r0 == 0) goto pc+2 */
BPF_MOV64_IMM(BPF_REG_1, 1),                					/* r1 = 1 */
BPF_XADD(BPF_DW, BPF_REG_0, BPF_REG_1, 0, 0), 					/* lock *(u64 *) r0 += r1 */
/* 设置返回值为0，退出程序 */
BPF_MOV64_IMM(BPF_REG_0, 0),                					/* r0 = 0 */
BPF_EXIT_INSN(),                            					/* return r0 */

Themis(x86):~# ./bpftool prog dump xlated id 4 
   0: (bf) r6 = r1
   1: (b7) r2 = 23
   2: (bf) r1 = r6
   3: (85) call bpf_skb_load_helper_8_no_cache#4600880
   4: (75) if r0 s>= 0x0 goto pc+2
   5: (ac) (u32) r0 ^= (u32) r0
   6: (95) exit
   7: (63) *(u32 *)(r10 -4) = r0
   8: (71) r1 = *(u8 *)(r6 +192)		//这条指令是做什么用的？
   9: (54) (u32) r1 &= (u32) 7
  10: (55) if r1 != 0x4 goto pc+8
  11: (bf) r2 = r10
  12: (07) r2 += -4
  13: (18) r1 = map[id:5]
  15: (85) call bpf_map_lookup_elem#76112
  16: (15) if r0 == 0x0 goto pc+2
  17: (61) r1 = *(u32 *)(r6 +176)
  18: (db) lock *(u64 *)(r0 +0) += r1
  19: (b7) r0 = 0
  20: (95) exit

```



* 为什么第一行代码删除之后无法执行？
  * 如何调试`BPF`汇编指令？
  
* `map`查询，如何调用`helper` 函数
  * 此处调用的函数为`array_map_lookup_elem()`，此处传入的是`map_fd`，是如何执行到这里的？
* 为什么直接传入`map_fd` 就可以，不同的用户态进程访问的时候对应不同的`map_fd`，是如何保证唯一的？而且是从内核态访问的设备
* `BPF insn{}结构体`、`BPF汇编`、`BPF insn{}二进制程序`、`BPF JIT汇编`、`BPF JIT二进制程序`之间如何转换？
* 









