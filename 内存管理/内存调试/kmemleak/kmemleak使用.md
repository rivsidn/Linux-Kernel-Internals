# kmemleak 使用

`kmemleak` 是 Linux 内核的内存泄漏检测器。

## 基本原理

### 跟踪分配和释放

`kmalloc()`、`kmem_cache_alloc()`、`vmalloc()` 等标准分配接口会通知 kmemleak。kmemleak 为每个尚未释放的对象记录：

- 起始地址与大小；
- 分配调用栈；
- 分配时间和状态。

对应的释放接口会删除记录。全部“尚未释放的对象”只是待判定的候选集合，并不表示它们都被当作引用根。

### 可达性扫描

一次扫描的简化过程如下：

1. 将所有候选对象标为白色（尚未发现引用）。
2. 扫描全局/每 CPU 数据、正在使用的页、任务内核栈（可配置）以及保存的寄存器等区域。
3. 扫描区域中的每一个机器字；若某个数值落在某个候选对象的地址范围内，则认为发现了指向该对象的引用，将它标为灰色并加入待扫描队列。
4. 依次扫描灰色对象中保存的值，递归找出更多可达对象。
5. 扫描结束仍为白色的已分配对象是 orphan，kmemleak 将其报告为疑似泄漏。

这里的“像指针”是数值判断，而不是了解 C 结构体的字段类型。
在 64 位系统上，当前实现从 8 字节对齐的位置按 `unsigned long`（8 字节）读取数值；若该数值指向对象内部，也可匹配到该对象。
正常结构体中的指针字段通常满足这种对齐方式；存放在 `__packed` 结构体或字节流中的未对齐指针，可能不会被发现。

因此 kmemleak 是保守检测器：

- 一个普通整数若恰好等于对象范围内的地址，会让泄漏对象被误认为仍可达（漏报）；
- 而指针藏在未扫描区域、以特殊编码保存或临时未出现在扫描区域时，可能让非泄漏对象被报告（误报）。

## 内核配置

在 `make menuconfig` 中进入 `Kernel hacking`，打开 `Kernel memory leak detector`。关键配置如下：

| 配置                                         | 是否需要 | 作用                                                                                 |
| ---                                          | ---      | ---                                                                                  |
| `CONFIG_DEBUG_KMEMLEAK=y`                    | 必需     | 编入 kmemleak，并自动选择 `DEBUG_FS`、`KALLSYMS`、栈回溯支持等依赖。                 |
| `CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF=y`        | 可选     | 默认不开启运行时跟踪，需追加内核命令行 `kmemleak=on` 才启用。                        |
| `CONFIG_DEBUG_KMEMLEAK_EARLY_LOG_SIZE=16000` | 可选     | 启动早期 kmemleak 尚未初始化时，记录分配/释放事件的缓冲条目数；范围为 200 到 40000。 |
| `CONFIG_DEBUG_KMEMLEAK_TEST=m`               | 可选     | 编译一个故意泄漏内存的测试模块，仅用于验证工具本身。                                 |


## 启动与运行时状态

默认情况下，编入且未配置 `CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF` 的 kmemleak 会在启动期间启用跟踪。

内核命令行可控制启动状态：

```text
kmemleak=off    # 启动时完全关闭；不会记录之后的分配，不能在运行期重新启用并补回记录
kmemleak=on     # 当 CONFIG_DEBUG_KMEMLEAK_DEFAULT_OFF=y 时，启动时启用
```

运行后写入 `off` 同样是不可逆操作。
关闭后只是保留此前报告所需的 kmemleak 元数据；写入 `clear` 才可清除这些元数据。

**NOTE: off 之后就不记录内存分配信息了，后续的扫描结果因为缺失了这一段的信息而导致不可信.**

kmemleak 会增加分配和释放路径的开销，并占用记录对象和调用栈所需的内存；扫描还会消耗 CPU 和缓存带宽。
它适合开发、问题复现和测试环境，不建议长期在性能敏感的生产设备上启用。

## 使用方法

### 访问 debugfs 接口

kmemleak 的控制与报告文件是 `/sys/kernel/debug/kmemleak`。先确认 debugfs 已挂载：

```bash
mountpoint -q /sys/kernel/debug || mount -t debugfs none /sys/kernel/debug
test -e /sys/kernel/debug/kmemleak && echo 'kmemleak is available'
```

若文件不存在，依次检查内核配置、是否使用了 `kmemleak=off`、以及 debugfs 是否挂载成功。

### 推荐的定向排查流程

对某驱动、模块或功能路径排查时，先清掉启动过程中已有的候选项，再复现问题：

```bash
# 1. 建立基线：不再显示当前已经报告的疑似泄漏
echo clear > /sys/kernel/debug/kmemleak

# 2. 执行待测操作：加载/卸载模块、反复打开关闭设备、触发错误路径等

# 3. 给异步释放、RCU 回调等留出完成时间；4.19 中对象最小报告年龄为 5 秒
sleep 5

# 4. 立即扫描并查看报告
echo scan > /sys/kernel/debug/kmemleak
cat /sys/kernel/debug/kmemleak
```

对并发或生命周期较复杂的路径，重复“复现 -> 等待 -> scan”几次。首次结果应结合对象的分配栈、释放时机和引用关系判断，不能把所有报告直接当成确定泄漏。

一个典型输出包含对象地址、大小、分配至今的时间，以及分配调用栈：

```text
unreferenced object 0xffff... (size 128):
  comm "worker", pid 123, jiffies ... (age 5.000s)
  hex dump (first 32 bytes): ...
  backtrace:
    [<...>] kmalloc_trace+
    [<...>] driver_probe+
```

优先从 `backtrace` 找到分配点，检查成功路径、错误回滚路径、超时/取消路径，以及模块卸载路径是否都有匹配的释放操作。较早的一个泄漏对象有时会使后续对象也失去唯一引用，因此应先修复报告列表前面的根因，再重新扫描。

### 控制命令

向同一个文件写入下列命令：

| 命令                                   | 作用                                                                                     |
| ---                                    | ---                                                                                      |
| `echo scan > .../kmemleak`             | 立即执行一次内存扫描。                                                                   |
| `cat .../kmemleak`                     | 查看已报告的疑似泄漏及分配栈。                                                           |
| `echo clear > .../kmemleak`            | 清除当前已报告的疑似泄漏；用于建立新的测试基线。关闭 kmemleak 后执行它还会释放内部记录。 |
| `echo scan=off > .../kmemleak`         | 停止自动扫描线程。不会停止分配/释放事件跟踪。                                            |
| `echo scan=on > .../kmemleak`          | 开启自动扫描线程。                                                                       |
| `echo scan=60 > .../kmemleak`          | 将自动扫描周期设为 60 秒；默认值是 600 秒，`scan=0` 等同停止自动扫描。                   |
| `echo stack=off > .../kmemleak`        | 不扫描任务内核栈，可减少栈中遗留值导致的漏报，但可能增加误报。                           |
| `echo stack=on > .../kmemleak`         | 扫描任务内核栈（默认开启）。                                                             |
| `echo 'dump=0xffff...' > .../kmemleak` | 将指定地址所在对象的信息打印到内核日志，用 `dmesg` 查看。                                |
| `echo off > .../kmemleak`              | 永久关闭本次启动中的 kmemleak，不能重新开启。                                            |

其中 `.../kmemleak` 均指 `/sys/kernel/debug/kmemleak`。手动 `scan` 适合在测试步骤完成后立即取样；自动扫描更适合长时间压力测试。

## 常见限制与辅助 API

- kmemleak 跟踪标准 kmalloc/slab/vmalloc 路径；Linux 4.19 文档明确说明 page allocation 和 `ioremap` 不在其跟踪范围内。
- `kmemleak_not_leak(ptr)`：将已知不需要释放的对象标记为非泄漏。
- `kmemleak_ignore(ptr)`：不扫描也不报告该对象；仅应对确认无需再追踪的对象使用。
- `kmemleak_no_scan(ptr)`：不扫描该对象内部保存的值；适用于确认对象不含有效引用的场景。
- `kmemleak_scan_area(ptr, size, gfp)`：只扫描对象中指定的区域，适合对象仅部分字段存放指针时减少误匹配。
- `kmemleak_erase(&ptr)`：在指针变量覆写前擦除旧值，避免旧地址残留在已扫描内存中造成漏报。

这些 API 定义在 `include/linux/kmemleak.h`。应先确认报告确属误报或漏报原因明确，再在驱动中使用；滥用会隐藏真实泄漏。

## 参考

- Linux 4.19：`Documentation/dev-tools/kmemleak.rst`
- Linux 4.19：`mm/kmemleak.c`
- Linux 4.19：`lib/Kconfig.debug`
