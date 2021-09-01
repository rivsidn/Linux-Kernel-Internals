











## 问题列表

| 序号    | 标题                         |
| ------- | ---------------------------- |
| [1](#1) | `CONFIG_DYNAMIC_FTRACE` 作用 |























* <a name="1">`CONFIG_DYNAMIC_FTRACE` 作用</a>

  可以这么理解，当开启动态 `ftrace` 功能时，内核会将之前的追踪函数调用指令修改成 `nop`，并将可以将可以追踪的函数放到一张表内。

  默认不开启的情况下，函数执行`nop`，此时开销很小。

  此时可以通过`set_ftrace_filter` `set_ftrace_notrace` 实现动态开启追踪函数的功能。

  涉及文件：

  | 文件                       | 作用         |
  | -------------------------- | ------------ |
  | available_filter_functions | 可跟踪的函数 |
  | set_ftrace_filter          | 要跟踪的函数 |
  | set_ftrace_notrace         | 不跟踪的函数 |

* 