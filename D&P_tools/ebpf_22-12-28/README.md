| BPF程序类型                 | 程序签名 | 使用场景 |
| --------------------------- | -------- | -------- |
| BPF_PROG_TYPE_SOCKET_FILTER |          |          |
|                             |          |          |
|                             |          |          |













## TODO

* `BPF程序类型` 有什么意义，能决定什么？

  梳理一下代码的执行流程

* `bpf_prog{ bpf_func }` 这个变量是如何填充的？

* `BPF内核` 部分可以使用的函数？ 

  * `load_byte()`
  * `__sync_fetch_and_add()`

  这些函数是哪里定义的？

* `BPF用户态` 部分可以使用的函数？是如何获取到的？

  | 函数             | 说明                         |
  | ---------------- | ---------------------------- |
  | bpf_create_map() | 函数是在哪里封装的？         |
  | BPF_MOV64_REG()  | 下边这些指令是在哪里定义的？ |
  | BPF_LD_ABS()     |                              |
  | BPF_STX_MEM()    |                              |

* `BPF attach类型` 的用处？

* `BPF`下载到内核的处理流程？

  * 程序的执行
  * 各种不同类型的`BPF`程序用处

* `pin` 到 `bpf` 文件系统的程序不会继续执行了，`pin` 这个动作有什么用？

* In addition, file descriptors referring to eBPF objects can be transferred over UNIX domain sockets.

  这个怎么操作？

* 







## 附录

### 参考资料

* [BPF 进阶笔记](https://arthurchiao.art/blog/bpf-advanced-notes-1-zh/#基础)
* 

