## 命令整理

基于`2.6.35.6` 内核。

| 命令     | 参数                       | 作用                                                         |
| -------- | -------------------------- | ------------------------------------------------------------ |
| bp       | [\<vaddr\>]                | 添加断点                                                     |
| bc       | \<bpnum\>                  | 删除断点                                                     |
| bd       | \<bpnum\>                  | 去使能断点                                                   |
| be       | \<bpnum\>                  | 使能断点                                                     |
| bl       |                            | 显示当前断点                                                 |
| bph      |                            | ？？？？？                                                   |
| ps       | [\<flags\>\|A]             | 显示特定状态的进程                                           |
| pid      | [\<pidnum\>]               | 切换到其他进程                                               |
| kill     | \<-signal\> \<pid\>        | 相进程发送信号                                               |
| bt       | [\<vaddr\>]                | 查看当前调用栈                                               |
| btp      | \<pid\>                    | 显示指定进程号的调用栈                                       |
| btt      | \<vaddr\>                  | 显示指定进程结构体的调用栈                                   |
| btc      |                            | 显示每个CPU的当前调用栈                                      |
| bta      | [DRSTCZEUIMA]              | 显示特定状态进程的调用栈                                     |
| md       | \<vaddr\> [\<line-count\>] | 显示虚拟地址内容，后边参数表示显示多少行<br>省略行数的时候有默认行数 |
| mdr      | \<vaddr\> \<bytes\>        | 显示虚拟地址内容，可以指定显示的字节数                       |
| mdp      | \<paddr\> [\<bytes\>]      | 显示物理地址内容，可以指定显示的字节数                       |
| mds      | \<vaddr\> [\<line-count\>] | 显示虚拟地址内容，可以指定显示行数                           |
| mm       | \<vaddr\> \<contents\>     | 修改内存内容(按照long长度修改)                               |
| rd       | 无                         | 显示寄存器内容(受当前CPU影响)                                |
| rm       | \<reg\> \<contents\>       | 修改寄存器内容                                               |
| ef       | \<vaddr\>                  | 显示异常(exception frame)信息                                |
| dmesg    | [lines]                    | 显示dmesg 信息                                               |
| lsmod    |                            | 显示当前加载的模块                                           |
| cpu      | [\<cpu\>]                  | 显示CPU或切换CPU                                             |
| ss       |                            | 单步执行                                                     |
| ssb      |                            | 单步执行直到碰到一个分支                                     |
| env      |                            | 查看环境变量                                                 |
| set      |                            | 设置环境变量                                                 |
| go       | [\<vaddr\>]                | 继续执行，可以通过指定地址跳转到指定位置执行                 |
| kgdb     |                            | 进入kgdd 模式                                                |
| reboot   |                            | 重启系统                                                     |
| defcmd   | name "usage" "help"        | 定义一个命令组合                                             |
| summary  |                            | 显示系统信息                                                 |
| grephelp |                            | 显示 grep 信息                                               |
| sr       | \<key\>                    | 等同于向`/proc/sysrq-trigger` 中写值                         |
|          |                            |                                                              |
| per\_cpu |                            | ？？？                                                       |
| ll       |                            | ？？？                                                       |
|          |                            |                                                              |

## 注意

* 进入`kdb`，此处显示的[0] 表示当前处于CPU0，可以通过`cpu` 命令切换

  > [0]kdb>

  当前CPU会对寄存器显示有影响

* `kdb`中，输入符号可以查看符号所在的虚拟地址，同样的，输入虚拟地址可以获取到附近符号表的偏移量

  > [0]kdb> schedule
  >
  > schedule = 0xfffffff8139eec0 (schedule)
  >
  > [0]kdb> 0xfffffff8139eec0
  >
  > 0xfffffff8139eec0 = 0xfffffff8139eec0 (schedule)

* 进程状态

  > * D = uninterruptible sleep
  > * R = running
  > * S = interruptible sleep
  > * T = stopped
  > * C = traced
  > * Z = exited and zombied
  > * E = exited and dead
  > * U = unrunnable
  > * I = idle
  > * M = daemon
  > * A = all

* 
