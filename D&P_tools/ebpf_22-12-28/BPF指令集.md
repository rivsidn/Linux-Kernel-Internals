## 指令格式

### 指令编码

| op(MSB) | dst_reg | src_reg | off  | imm(LSB) |
| ------- | ------- | ------- | ---- | -------- |
| 8       | 4       | 4       | 16   | 32       |

### op

| code(MSB) | source | class(LSB) |
| --------- | ------ | ---------- |
| 4         | 1      | 3          |





85 00 00 00 50 29 01 00





```c
//对应的C结构体
struct bpf_insn {
    __u8 code;			/* opcode */
    __u8 dst_reg:4;		/* dest register */
    __u8 src_reg:4;		/* source register */
    __s16 off;			/* singed offset */
    __s32 imm;			/* signed immediate constant */
}
```





