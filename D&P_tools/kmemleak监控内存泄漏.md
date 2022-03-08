`kmemleak` 可以用于检测内核内存泄漏。



## 工具使用

* 内核编译选项

  | 选项                                 | 作用                                        |
  | ------------------------------------ | ------------------------------------------- |
  | CONFIG_DEBUG_KMEMLEAK                | 使能kmemleak                                |
  | CONFIG_DEBUG_KMEMLEAK_EARLY_LOG_SIZE | 设置使能前日志缓冲区大小                    |
  | CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF    | 默认关闭kememleak，需要设置内核启动参数开启 |

* 操作接口

  ```bash
  # 挂载调试文件系统
  mount -t debugfs nodev /sys/kernel/debug/
  # 触发立即扫描
  echo scan > /sys/kernel/debug/kmemleak
  # 查看调试信息
  cat /sys/kernel/debug/kmemleak
  ```

* 可用参数
  | 命令        | 解释                                                  |
  | ----------- | ----------------------------------------------------- |
  | off         | 关闭`kmemleak` 功能，该操作不可逆                     |
  | stack=on    | 使能栈扫描(默认)                                      |
  | stack=off   | 关闭栈扫描                                            |
  | scan=on     | 开启内核扫描线程(默认)                                |
  | scan=off    | 关闭内核自动扫描                                      |
  | scan=<secs> | 设置自动扫描时间(默认600s，0 表示关闭)                |
  | scan        | 触发内核内存扫描                                      |
  | clear       | 清空扫描结果；`kmemleak` 关闭时，释放 kmemleak 结构体 |
  | dump=<addr> | 获取`addr` 位置的`obj`信息，通过`dmesg` 查看          |



## 实现原理

跟踪内核内存申请函数，将内存申请到的所有`object`信息(地址、长度、调用栈等)添加到红黑树中。

扫描的时候：

1. 将所有的`object` 设置为白色
2. 扫描数据段、栈段的内存，检查红黑树中的值，如果检查到指向红黑树中`object`的节点，则将该节点添加到灰色链表中
3. 扫描灰色链表中的`object`，直到完全扫描结束
4. 此时依旧为白色的节点被认为是存在内存泄漏

**TIPs: 跑内核自带示例发现可能不能输出所有的泄漏点，内存泄漏问题通常是长时间、持续的内存泄漏，通过该工具定位应该足够了。**



## 参考资料

* 内核文档`Documentation/kmemleak.txt`

