## bpf_asm



## bpf_dbg



## bpf_jit_disasm

### 开启调试模式

```bash
# 开始调试模式，程序执行时后台会输出调试信息
echo 2 > /proc/sys/net/core/bpf_jit_enable
```

### 反汇编

```bash
# 输出文件对应的汇编
bpf_jit_disasm -f <file>
```

### 参数说明

`/proc/sys/net/core/bpf_jit_enable` 参数说明：

| 参数选项 | 说明                                                   |
| -------- | ------------------------------------------------------ |
| 0        | 默认关闭                                               |
| 1        | 正常编译                                               |
| 2        | 调试模式，开启调试模式后，会将生成的操作码输出到日志中 |

`bpf_jit_disasm` 选项说明：

| 选项      | 说明                                                         |
| --------- | ------------------------------------------------------------ |
| -O <file> | 输出二进制镜像到文件中，就是生成操作码的二进制镜像到文件中 **TODO:这里有什么用？** |
| -o        | 显示对应的操作码                                             |
| -f <file> | 从文件中读取操作码镜像文件                                   |
| -h        | 显示帮助信息                                                 |



## bpftool

### bpftool-map

```bash
# 显示map信息
bpftool map show   [MAP]
# 输出map内容
bpftool map dump    MAP
# 更新
bpftool map update  MAP  key BYTES   value VALUE [UPDATE_FLAGS]
# 查询
bpftool map lookup  MAP  key BYTES
# 获取下一个
bpftool map getnext MAP [key BYTES]
# 删除
bpftool map delete  MAP  key BYTES
# 将map pin到bpffs文件系统
bpftool map pin     MAP  FILE
# 输出帮助信息
bpftool map help
```

### bpftool-prog

```bash
# 显示加载的程序
bpftool prog show [PROG]
# 输出eBPF指令
bpftool prog dump xlated PROG [{ file FILE | opcodes }]
# 输出程序jited指令
bpftool prog dump jited PROG [{ file FILE | opcode }]
# 将程序pin到bpffs文件系统
bpftool prog pin PROG FILE
# 输出帮助信息
bpftool prog help
```

