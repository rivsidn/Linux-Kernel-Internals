
READ_ONCE() 和 WRITE_ONCE() 是 Linux 内核中用来防止编译器优化的宏.

举例说明.

## 编译器优化示例



### 多次读取被合并

```c
   while (tmp = a)          // 原始代码
       do_something_with(tmp);
 
   // 被优化成：
   if (tmp = a)            // 编译器"优化"
       for (;;)
           do_something_with(tmp);  // 死循环！
```

### 编译器省略存储
 
```c
   a = 0;
   /* 其他代码 */
   a = 0;  // 编译器可能省略这次写入
 
   // 使用 WRITE_ONCE() 强制写入
   WRITE_ONCE(a, 0);
```
 
### 编译器重新加载变量
 
```c
  while (tmp = a)
      do_something_with(tmp);

  // 编译器可能优化成：
  while (a)
      do_something_with(a);  // 每次都重新读取 a
```

## 附录

### AI

> ● READ_ONCE() 和 WRITE_ONCE() 是 Linux 内核中用来防止编译器优化的宏，它们的作用是：
> 
>   主要功能
> 
>   1. 防止编译器优化：确保编译器真正生成内存访问指令，而不是优化掉
>   2. 防止编译器重排序：保证编译器不会改变内存访问的顺序
>   3. 防止 load/store tearing：确保对齐的内存访问是原子的
> 
>   为什么需要它们？
> 
>   看文档中 memory-barriers.txt#L1394-1668 的例子：
> 
>   1. 防止多次读取被合并
> 
>   // 没有 READ_ONCE()，编译器可能优化成：
>   while (tmp = a)          // 原始代码
>       do_something_with(tmp);
> 
>   // 被优化成：
>   if (tmp = a)            // 编译器"优化"
>       for (;;)
>           do_something_with(tmp);  // 死循环！
> 
>   2. 防止编译器省略存储
> 
>   a = 0;
>   /* 其他代码 */
>   a = 0;  // 编译器可能省略这次写入
> 
>   // 使用 WRITE_ONCE() 强制写入
>   WRITE_ONCE(a, 0);
> 
>   3. 防止编译器重新加载变量
> 
>   while (tmp = a)
>       do_something_with(tmp);
> 
>   // 编译器可能优化成：
>   while (a)
>       do_something_with(a);  // 每次都重新读取 a
> 
>   什么时候必须使用？
> 
>   在多核并发场景下，当变量可能被其他 CPU 修改时必须使用：
> 
>   1. 无锁数据结构
>   2. 设备驱动（MMIO 访问）
>   3. 中断处理程序与主程序共享数据
>   4. RCU 等并发机制
> 
>   实现原理
> 
>   READ_ONCE() 和 WRITE_ONCE() 通过 volatile 转换实现：
>   #define READ_ONCE(x) (*(volatile typeof(x) *)&(x))
> 
>   volatile 告诉编译器：
>   - 不要缓存这个值
>   - 每次都真正访问内存
>   - 不要重排序相关的访问
> 
>   注意事项
> 
>   1. 它们只影响编译器，不影响 CPU
>     - CPU 仍可能重排序，需要内存屏障（mb(), smp_mb() 等）
>   2. 对已经是 volatile 的变量不需要
>     - 如 jiffies 已经是 volatile，无需 READ_ONCE(jiffies)
>   3. 单线程代码不需要
>     - 只有在并发访问共享数据时才需要
> 
>   简而言之：READ_ONCE() 和 WRITE_ONCE() 是并发编程的基础工具，防止编译器"太聪明"而破坏了多核环境下的正确性。

