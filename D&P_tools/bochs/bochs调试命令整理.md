| 命令              | 解释             |
| ----------------- | ---------------- |
| h \| help         | 输出调试命令列表 |
| h \| help command | 输出命令描述     |



## 调试器控制

| 命令                                  | 解释                                                         |
| ------------------------------------- | ------------------------------------------------------------ |
| q \| quit \| exit                     | 退出调试                                                     |
| set \<regname\> = \<expr\>            | 设置寄存器的值                                               |
| set eflags = \<expr\>                 | 设置eflags 寄存器的值，并不是所有的值都是可以设置的          |
| set $cpu = \<N\>                      | 设置当前调试的CPU 号                                         |
| set ${auto_disassemble} = 1 / 0       | 开启或者关闭自动反汇编，反汇编下一条要执行的指令             |
| set u \| disasm \| dissemble on / off | 开启或者关闭自动反汇编                                       |
| instrument \<command\>                | 调用`BX_INSTR_DEBUG_CMD` 回调函数<br/>该功能需要`configure`过程中添加 `--enable-instrumentation` 参数并修改代码实现，<br/>当前该命令不起任何作用，具体可以查看源码中的 `instrument/stubs/` 目录 |
| show                                  | 查看当前显示模式                                             |
| show mode                             | CPU模式切换时输出模式切换信息<br/>类似:<br/>00000327302: switched from 'real mode' to 'protected mode'<br/>00001219911: switched from 'protected mode' to 'real mode' |
| show int                              | 中断发生时输出日志信息，该模式等同于同时打开`softint` `extint` `iret` 三个开关 |
| show softint                          | 软件中断发生时，输出日志信息                                 |
| show extint                           | 外部中断发生时，输出日志信息                                 |
| show iret                             | 调用`iret`退出中断模式时，输出日志信息                       |
| show call                             | 执行 `call` 指令时，输出日志信息                             |
| show all                              | 打开所有显示开关`call` `softint` `extint` `iret` `mode`      |
| show off                              | 关闭所有显示开关                                             |
| show dbg_all                          | 开启所有调试开关，通过源码发现就是打开中断、异常开关。<br/>该开关优于`show int` 的一点是可以查看中断号。 |
| show dbg_none                         | 关闭所有调试开关                                             |
| trace on / off                        | 使能或者去使能输出每条刚执行结束的指令，与 *set u \| disasm \| dissemble on/off* 相对 |
| trace-reg on / off                    | 执行命令之后输出所有寄存器的值，开启或关闭                   |
| trace-mem on / off                    | 每次执行指令输出内存访问信息功能开启或关闭                   |
| u \| disasm /count \<start\>          | 反汇编`start` 开始的 `count` 条指令                          |
| u \| disasm \<start\> \<end\>         | 反汇编`start` 到`end` 的指令                                 |
| u \| disasm switch-mode               | 汇编格式切换                                                 |
| u \| disasm hex on / off              | 修改汇编偏移量和移位的显示格式                               |
| u \| disasm size = n                  | n 可能的值为 16、32、64，告诉调试器段长度                    |
| ldsym [global] \<filename\> [offset]  | 【**TODO**】文件中加载符号表                                 |
| slist [string]                        | 输出前缀是`string` 的符号                                    |



## 执行控制

| 命令                  | 解释     |
| --------------------- | -------- |
| c \| cont \| continue |          |
| s \| step             | 单步执行 |
| p \| n \| next        | 单步执行 |
|                       |          |



## 添加断点

| 命令                          | 解释                                             |
| ----------------------------- | ------------------------------------------------ |
| pb \| pbreak \| b \| break    | 添加物理地址断点                                 |
| vb \| vbreak                  | 添加虚拟断点                                     |
| lb \| lbreak                  | 添加线性地址断点                                 |
| bpe                           | 使能断点                                         |
| bpd                           | 去使能断点                                       |
| blist                         | 查看所有断点                                     |
| d \| del \| delete            | 删除断点                                         |
| sb                            | 添加时间间隔断点(可以理解成执行多少条指令后停止) |
| sba                           | 添加绝对时间断点(可以理解成执行到哪里结束)       |
| modebp                        | 模式切换断点开关                                 |
| vmexitbp                      | **VMEXIT** 切换断点开关                          |
| watch                         | 输出当前观测点状态                               |
| watch stop / continue         | 触发观测点时停止模拟或者输出日志继续执行         |
| watch r \| read addr \<len\>  | 添加物理地址读观测点                             |
| watch w \| write addr \<len\> | 添加物理地址写观测点                             |
| unwatch                       | 删除所有观测点                                   |
| unwatch addr                  | 删除执行地址观测点                               |
|                               |                                                  |



## CPU和内存内容

| 命令                                    | 解释                                                 |
| --------------------------------------- | ---------------------------------------------------- |
| x  /nuf \<addr\>                        | 显示线性地址内容，显示格式可以参见 **help** 信息     |
| xp /nuf \<addr\>                        | 显示物理地址内容                                     |
| setpmem \<addr\> \<datasize\> \<val\>   | 设置物理地址内容                                     |
| writemem \<filename\> \<laddr\> \<len\> | 将线性地址中内容转存到文件中                         |
| crc \<addr1\> \<addr2\>                 | 显示物理地址范围的`crc`                              |
| info break                              | 显示断点信息                                         |
| info cpu                                | 【**会引起虚拟机配崩溃**】显示所有`cpu` 的寄存器信息 |
| info idt [NUM] [NUM] ...                | 显示中断描述符表信息                                 |
| info ivt [NUM] [NUM] ...                | 显示中断向量表信息                                   |
| info gdt [NUM] [NUM] ...                | 显示全局描述符表信息                                 |
| info tss                                | 显示当前进程状态寄存器                               |
| info tab                                | 显示页表信息                                         |
| info eflags                             | 显示eflag 寄存器信息                                 |
| info symbols [string]                   | 显示以 `string` 为前缀的符号表                       |
| info device                             | 显示支持该命令的设备                                 |
| info device [string]                    | 显示状态信息                                         |
| info device [string] [string]           | 显示状态信息，添加选项                               |
| r \| reg \| regs \| registers           | 显示`CPU`寄存器信息                                  |
| fp \| fpu                               | 输出`FPU`状态                                        |
| mmx                                     | 显示`MMX`状态                                        |
| xmm \| sse                              | 【**会引起虚拟机崩溃**】显示`SSE`状态                |
| sreg                                    | 显示段寄存器信息                                     |
| dreg                                    | 显示调试寄存器信息                                   |
| creg                                    | 显示控制寄存器信息                                   |
| page \<addr\>                           | 线性地址转换成物理地址                               |
| ptime                                   | 显示当前时间(可以理解成当前执行了多少条指令)         |
| print-stack [num_words]                 | 显示栈信息                                           |
| calc \| ?                               | 计算一个值并显示结果                                 |
|                                         |                                                      |



## bochs参数树

| 命令                   | 解释                                                         |
| ---------------------- | ------------------------------------------------------------ |
| show "param" [xml]     | 显示`bochs` 参数树，示例：<br/>show "."<br/>show "cpu0"<br/>show "ioapic" |
| restore "cpu0"         | 从当前路径恢复`cpu0`                                         |
| restore "cpu0" "/save" | 从路径`save` 处回复`cpu0`                                    |
|                        |                                                              |

