## 传统PC启动


```bash
硬件上电
   ↓
BIOS / UEFI  ←（硬件初始化 + 读取磁盘分区表）
   ↓
GRUB         ←（显示菜单，选择 OS，加载内核）
   ↓
Linux / Windows / 其他 OS
```

## 嵌入式系统启动

```bash
硬件上电
   ↓
ROM Boot（SoC 内部固定代码）
   ↓
U-Boot (SPL + main)
   ↓
Linux Kernel / RTOS / Android

```

在 PC 上：UEFI + GRUB 是两层结构。
在嵌入式上：U-Boot 通常一肩挑两层的工作。
