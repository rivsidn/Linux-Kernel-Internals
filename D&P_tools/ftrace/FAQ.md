



## 问题列表

| 序号    | 标题                           |
| ------- | ------------------------------ |
| [1](#1) | `CONFIG_DYNAMIC_FTRACE` 作用   |
| [2](#2) | `ftrace`与`event`之间关系      |
| [3](#3) | `event`与`tracepoints`之间关系 |











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

* <a name="2">`ftrace`与`event`之间关系</a>

  `ftrace` 与 `event` 是两个相互独立的跟踪机制，可以实现单独编译．

  两个都通过tracefs 提供控制，查看接口．

  `tracefs`　接口中有的单独只作用于`ftrace` ，有的只作用于`event` (`set_event`, `set_event_pid` 等)．

* <a name="3">`event`与`tracepoints`之间关系</a>

   `event`是  `tracepoints`的应用，`tracepoints` 是`event` 底层实现机制．

* 