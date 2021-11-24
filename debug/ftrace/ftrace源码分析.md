1. 看一下文档`ring-buffer-design.txt`

2. 先读`ring_buffer.c`

   1. 四种状态如何理解？

      ```c
      NORMAL
      HEAD
      UPDATE
      MOVED
      ```

   2. 

3. 





```c

/*   +------+
 *   |reader|          RING BUFFER
 *   |page  |
 *   +------+        +---+   +---+   +---+
 *                   |   |-->|   |-->|   |
 *                   +---+   +---+   +---+
 *                     ^               |
 *                     |               |
 *                     +---------------+
 *
 *
 *   +------+
 *   |reader|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *                   |   |-->|   |-->|   |
 *                   +---+   +---+   +---+
 *                     ^               |
 *                     |               |
 *                     +---------------+
 *
 *
 *   +------+
 *   |reader|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *      ^            |   |-->|   |-->|   |
 *      |            +---+   +---+   +---+
 *      |                              |
 *      |                              |
 *      +------------------------------+
 *
 *
 *   +------+
 *   |buffer|          RING BUFFER
 *   |page  |------------------v
 *   +------+        +---+   +---+   +---+
 *      ^            |   |   |   |-->|   |
 *      |   New      +---+   +---+   +---+
 *      |  Reader------^               |
 *      |   page                       |
 *      +------------------------------+
 */
```









## TODO

* 

* 结构体作用
  * trace_array{}
  
* options 是如何添加的，为什么nop 的两个选项没有添加上

* 如何与`traefs` 交互？

* `ring_buffer.c` 的实现？

* `trace_boot.c` 做什么用的？

* `debugfs` 文件系统实现？

* `trace_branch.c` 功能？与其他的 `tracer` 之间的关系？

* `ftrace_event.h` 文件作用？

* `trace_events.c` 实现？

* `kmemcheck_bitfield_begin()` 使用？

* 下边这些宏的用处

  ```c
  #define RB_FLAG_NORMAL	0UL
  #define RB_FLAG_HEAD	1UL
  #define RB_FLAG_UPDATE	2UL
  
  #define RB_FLAG_MASK	3UL
  
  #define RB_PAGE_MOVED	4UL
  ```

  

* 





