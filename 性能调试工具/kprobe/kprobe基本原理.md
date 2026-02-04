
基于 `2.6.35.6` 内核.

## 实现原理

### Kprobe

Kprobe 能够探测函数的任意位置.

- kprobe 注册，替换探测指令为`int 3`，并存储`probed instruction`
- 程序执行到探测点时，会触发`int 3`，然后执行`pre_handler`
- 执行`probed instruction`，执行`post_handler`
- 继续执行后续指令

### Jprobe

可以通过Jprobe 查看函数参数.

Jprobe 内部实现依赖与Kprobe，`int 3` 添加在函数起始位置.

- Jprobe 注册，设置`int 3`，`pre_handler` 设置为`setjmp_pre_handler()`
- 函数执行到探测点时，会执行`handler`(handler 必须要与probe 函数有相同的函数签名)
- 执行结束之后，通过`jprobe_return()`返回到追踪函数中执行
- 可以设置并执行`post_handler` 函数

### Kretprobe

不仅可以注册`entry_handler`，在函数开始时执行；还可以注册`handler` 在函数退出时执行，退出时查看函数返回值.

Kretprobe 内部同样依赖于Kprobe，`int 3` 添加在函数起始位置.

- Kretprobe 在函数起始位置添加异常指令
- 异常触发之后，执行`pre_handler_kretprobe`，初始化`kretprobe_instance{}`，将返回地址修改为trampoline
- 执行`entry_handler` 函数
- 函数返回之后执行到跳板函数
- 跳板函数执行`handler`
- 查询记录的返回地址，重新返回到caller

由于同一个函数可能会有多个caller，所以返回地址需要记录多份.

于Jprobe 不同，Kretprobe 无法执行将内核Kprobe 的`post_handler`，注册的时候会将其设置为空.


## 附录

### 相关图

- [kprobe工作原理图](/home/yuchao/github/kernel_graph/2.6.35.6/kernel/kprobe.drawio)

