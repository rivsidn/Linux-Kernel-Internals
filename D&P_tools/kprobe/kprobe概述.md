`kprobe` 通过向代码中插入 `int 3` 指令来实现，所以理论调试代码上可以在插入到任何位置，可以在处理函数中修改寄存器的值，修改代码执行流程，livepatch 等。

如果是跟踪函数的调用返回，通过`ftrace` 就可与实现。

当跟踪函数内部执行流程，由于编译器的复杂性，以及代码更新等因素，容易导致程序不可控。

所以，这部分没有花费太多精力，仅仅用于了解。

