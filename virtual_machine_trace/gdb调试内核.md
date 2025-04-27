
## gdb调试内核

### gdb调试内核模块

* 查看模块加载地址
  ```bash
  # lsmod xxx.ko
  xxx.ko 1234 0 - Live 0xffffffffc0000000
  ```
* `GDB` 中加载符号模块
  ```gdb
  add-symbol-file xxx.ko 0xffffffffc0000000
  ```
* 添加断点，断点添加过程中不需要指定模块名
  ```gdb
  break function
  ```


