| BPF程序类型                 | 使用场景 |
| --------------------------- | -------- |
| BPF_PROG_TYPE_SOCKET_FILTER |          |
|                             |          |
|                             |          |













## TODO

* 不同进程、内核程序之间共享`map`

* `pin` 到 `bpf` 文件系统的程序不会继续执行了，`pin` 这个动作有什么用？

* In addition, file descriptors referring to eBPF objects can be transferred over UNIX domain sockets.

  这个怎么操作？

* `BPF内核` 部分可以使用的函数？ 

  * `load_byte()`

    该函数属于`llvm` 的内建函数，该函数经过`clang`处理之后，自动转换成eBPF指令。

  * `__sync_fetch_and_add()`

    同样属于`llvm` 中的内嵌函数，表示`atomic` 加操作。

  这些函数是哪里定义的？

* `BPF用户态` 部分可以使用的函数？是如何获取到的？

  | 函数                         | 说明               |
  | ---------------------------- | ------------------ |
  | bpf_create_map()             | libbpf 中定义      |
  | bpf_create_map_in_map_node() |                    |
  | bpf_create_map_node()        | 与上边函数的差异？ |
  | BPF_MOV64_REG()              | libbpf 中定义      |
  | BPF_LD_ABS()                 |                    |
  | BPF_STX_MEM()                |                    |

* `bpf_prog{ bpf_func }` 这个变量是如何填充的？

* `bpf` 程序汇编指令？

  * `sock_example.c` 中，这一串指令如何理解？
  * 如何调试汇编指令？

* 分析`clang` 生成的`bpf object`  文件格式







## 附录

### 参考资料

* [BPF 进阶笔记](https://arthurchiao.art/blog/bpf-advanced-notes-1-zh/#基础)
* 

