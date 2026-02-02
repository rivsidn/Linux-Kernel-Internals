# Summary

- [Introduction](README.md)

## 内核开发

- [内核开发](developer/README.md)
  - [patch分析linux内核](developer/patch分析linux内核.md)
  - [tig工具使用](developer/tig工具使用.md)
  - [内核漏洞更新](developer/内核漏洞更新.md)

## 内核编译

- [内核编译](compile/README.md)
  - [bzImage转换成vmlinux](compile/bzImage转换成vmlinux.md)
  - [内核链接脚本分析](compile/内核链接脚本分析.md)
  - [kconfig语法](compile/kconfig语法.md)

## 代码规范

- [代码规范](代码规范/README.md)
  - [内核错误码](代码规范/内核错误码.md)


## 内核初始化

- [内核初始化](start_kernel/README.md)

## 内核驱动

- [内核驱动](内核驱动/README.md)

## 进程管理

- [进程管理](进程管理/README.md)
  - [进程调度](进程管理/进程调度.md)
  - [进程状态](进程管理/进程状态.md)
  - [工作队列](进程管理/工作队列.md)
  - [等待队列](进程管理/等待队列.md)
  - [内核线程](进程管理/内核线程.md)

### 进程间通信

  - [进程间信号](进程管理/进程间信号.md)

## 文件系统

- [文件系统](文件系统/README.md)

### proc文件系统

  - [proc文件系统](文件系统/proc文件系统/README.md)
    - [常用接口](文件系统/proc文件系统/常用接口.md)

## 内存管理

- [内存管理](mm/README.md)
  - [内存管理硬件基础](mm/内存管理硬件基础.md)
  - [SLAB内存管理](mm/SLAB内存管理.md)
  - [SLUB内存管理](mm/SLUB内存管理.md)
  - [内存问题定位](mm/debug/README.md)
    - [PAGEALLOC调试选项](mm/debug/PAGEALLOC调试选项.md)
    - [SLUB_DEBUG调试选项](mm/debug/SLUB_DEBUG调试选项.md)

## 中断与软中断

- [中断软中断](中断与软中断/README.md)
  - [内核软中断](中断与软中断/内核软中断.md)
  - [定时器实现](中断与软中断/定时器实现.md)

## 内核数据结构

- [内核数据结构](内核数据结构/README.md)
  - [链表](内核数据结构/链表.md)

## 内核加密算法

- [内核加密算法](内核加密算法/README.md)
  - [加密接口](内核加密算法/加密接口.md)
  - [sm2算法内核编译](内核加密算法/sm2算法内核编译.md)

## 内核同步机制

- [内核同步](内核同步机制/README.md)
  - [自旋锁](内核同步机制/自旋锁.md)
  - [顺序锁](内核同步机制/顺序锁.md)
  - [编译器屏障](内核同步机制/编译器屏障.md)
  - [缓存一致性协议](内核同步机制/缓存一致性协议.md)
  - [内存屏障基础](内核同步机制/内存屏障基础.md)
  - [内存屏障实例](内核同步机制/内存屏障实例.md)
  - [等待队列](内核同步机制/等待队列.md)
  - [位等待队列](内核同步机制/位等待队列.md)

## 内核交互

- [内核交互](内核交互/README.md)
  - [ioctl使用](内核交互/ioctl使用.md)
  - [netlink基础](内核交互/netlink基础.md)
  - [传统netlink](内核交互/传统netlink/README.md)
    - [rtnetlink使用](内核交互/传统netlink/rtnetlink使用.md)
  - [通用netlink使用](内核交互/通用netlink/README.md)
    - [通用netlink内核注册](内核交互/通用netlink/通用netlink内核注册.md)
    - [通用netlink用户通信](内核交互/通用netlink/通用netlink用户通信.md)

## 内核网络

- [内核网络](内核网络/README.md)
  - [skb申请与释放](内核网络/skb申请与释放.md)
  - [内核收包(二)](内核网络/内核收包(二).md)
  - [vlan分析](内核网络/vlan分析.md)
  - [br\_vlan分析](内核网络/br_vlan分析.md)
  - [macvlan源码分析](内核网络/macvlan源码分析.md)
  - [macvtap分析](内核网络/macvtap分析.md)
  - [synproxy源码分析](内核网络/synproxy源码分析.md)
  - [xfrm分析](内核网络/xfrm分析.md)
  - [桥转发fdb表](内核网络/桥转发fdb表.md)

### netfilter

  - [netfilter](内核网络/netfilter/README.md)
    - [链接跟踪](内核网络/netfilter/链接跟踪/README.md)
      - [链接跟踪数据结构](内核网络/netfilter/链接跟踪/链接跟踪数据结构.md)
      - [链接跟踪会话创建](内核网络/netfilter/链接跟踪/链接跟踪会话创建.md)
      - [链接跟踪会话老化](内核网络/netfilter/链接跟踪/链接跟踪会话老化.md)
      - [链接跟踪netlink机制](内核网络/netfilter/链接跟踪/netlink/README.md)
        - [会话查询](内核网络/netfilter/链接跟踪/netlink/会话查询.md)
      - [链接跟踪会话杂七杂八](内核网络/netfilter/链接跟踪/链接跟踪会话杂七杂八.md)

## 调试&性能工具

- [调试&性能工具](性能调试工具/README.md)

### eBPF

  - [eBPF](性能调试工具/ebpf/README.md)
  - [BPF](性能调试工具/ebpf_22-12-28/README.md)
    - [BPF程序基础](性能调试工具/ebpf_22-12-28/BPF程序基础.md)
    - [BPF程序编译](性能调试工具/ebpf_22-12-28/BPF程序编译.md)
    - [BPF-MAP使用](性能调试工具/ebpf_22-12-28/BPF-MAP使用.md)
    - [BPF工具使用](性能调试工具/ebpf_22-12-28/BPF工具使用.md)

### kgdb&kdb

  - [kgdb](性能调试工具/kgdb/README.md)
    - [kdb使用](性能调试工具/kgdb/kdb使用.md)
    - [kgdb使用](性能调试工具/kgdb/kgdb使用.md)


### perf



## 内核调试

- [内核调试](内核调试/README.md)
  - [debootstrap命令](内核调试/debootstrap命令.md)
  - [制作docker镜像](内核调试/制作docker镜像.md)
  - [构建QEMU根文件系统](内核调试/构建QEMU根文件系统.md)
  - [gdb命令](内核调试/gdb命令.md)
  - [内核调试-2.6.12](内核调试/内核调试-2.6.12.md)
  - [4.4.155内核调试](内核调试/4.4.155/README.md)
    - [搭建内核编译环境](内核调试/4.4.155/搭建内核编译环境.md)
    - [搭建内核调试环境](内核调试/4.4.155/搭建内核调试环境.md)

### GDB

  - [内核GDB脚本](内核调试/内核GDB脚本.md)
  - [内核GDB脚本实现](内核调试/内核GDB脚本实现.md)

### lockdep

  - [lockdep实现](内核调试/lockdep实现.md)
  - [lockdep分析](内核调试/lockdep分析.md)

## 虚拟机

- [虚拟机](virtual_machine/README.md)
  - [QEMU](virtual_machine/qemu/README.md)
    - [QEMU内核调试环境-2.6.12](virtual_machine/qemu/QEMU内核调试环境-2.6.12.md)
    - [QEMU内核调试环境-2.6.26](virtual_machine/qemu/QEMU内核调试环境-2.6.26.md)
    - [QEMU内核调试环境-4.19](virtual_machine/qemu/QEMU内核调试环境-4.19.md)
    - [QEMU网络环境](virtual_machine/qemu/QEMU网络环境.md)
    - [QEMU\_TODO](virtual_machine/qemu/QEMU_TODO.md)
  - [vmware\_2.4编译环境](virtual_machine/vmware_2.4编译环境.md)
  - [vmware\_2.6编译环境](virtual_machine/vmware_2.6编译环境.md)
  - [vitrual-manager安装](virtual_machine/virtual-manager安装.md)
  - [docker常用命令](virtual_machine/docker常用命令.md)

- [虚拟机搭建内核调试环境](virtual_machine_trace/README.md)
  - [virsh命令](virtual_machine_trace/virsh命令.md)
  - [QEMU内核调试环境-2.6.12](virtual_machine_trace/QEMU内核调试环境-2.6.12.md)
  - [QEMU内核调试环境-4.4.155](virtual_machine_trace/QEMU内核调试环境-4.4.155.md)
  - [gdb调试内核](virtual_machine_trace/gdb调试内核.md)
 
## 其他

- [其他](miscs/README.md)

