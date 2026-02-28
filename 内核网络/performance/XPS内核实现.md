
## 基本原理

## 参数配置





## 附录

### 配置接口

```
==== XPS Configuration

XPS is only available if the kconfig symbol CONFIG_XPS is enabled (on by
default for SMP). The functionality remains disabled until explicitly
configured. To enable XPS, the bitmap of CPUs/receive-queues that may
use a transmit queue is configured using the sysfs file entry:

For selection based on CPUs map(基于CPU映射):
/sys/class/net/<dev>/queues/tx-<n>/xps_cpus

For selection based on receive-queues map(基于接收队列映射):
/sys/class/net/<dev>/queues/tx-<n>/xps_rxqs

```
