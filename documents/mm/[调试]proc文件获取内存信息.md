通过文件获取内核内存信息，基于 `4.4.155`  内核分析。



## /proc/meminfo

| 名称         | 意义 | 拓展说明 |
| ------------ | ---- | ---- |
| MemTotal             | 可供内核分配的内存总量 | 少于物理内存，主板/固件会占用一部分内存；<br/>内核也会占用一部分内存 |
| MemFree             | 系统尚未分配的内存 |  |
| MemAvailable             | 可用内存估计值 |  |
| Buffers             |      |      |
| Cached             |      |      |
| SwapCached             |      |      |
| Active             |      |      |
| Inactive             |      |      |
| Active(anon)             |      |      |
| Inactive(anon)             |      |      |
| Active(file)             |      |      |
| Inactive(file)             |      |      |
| Unevictable             |      |      |
| Mlocked             |      |      |
| SwapTotal             |      |      |
| SwapFree             |      |      |
| Dirty             |      |      |
| Writeback             |      |      |
| AnonPages             |      |      |
| Mapped             |      |      |
| Shmem             |      |      |
| Slab             |      |      |
| SReclaimable             |      |      |
| SUnreclaim             |      |      |
| KernelStack             |      |      |
| PageTables             |      |      |
| NFS_Unstable             |      |      |
| Bounce             |      |      |
| WritebackTmp             |      |      |
| CommitLimit             |      |      |
| Committed_AS             |      |      |
| VmallocTotal             |      |      |
| VmallocUsed             |      |      |
| VmallocChunk             |      |      |
| AnonHugePages             |      |      |
| CmaTotal             |      |      |
| CmaFree             |      |      |
| HugePages_Total             |      |      |
| HugePages_Free             |      |      |
| HugePages_Rsvd             |      |      |
| HugePages_Surp             |      |      |
| Hugepagesize             |      |      |
| DirectMap4k             |      |      |
| DirectMap2M             |      |      |



### 分析



### 实例

```
MemTotal:        6836460 kB
MemFree:         5514196 kB
MemAvailable:    5419072 kB
Buffers:             692 kB
Cached:           788508 kB
SwapCached:            0 kB
Active:           788004 kB
Inactive:         347628 kB
Active(anon):     787288 kB
Inactive(anon):   347628 kB
Active(file):        716 kB
Inactive(file):        0 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:             0 kB
SwapFree:              0 kB
Dirty:                 0 kB
Writeback:             0 kB
AnonPages:        346416 kB
Mapped:            80712 kB
Shmem:            788504 kB
Slab:             136088 kB
SReclaimable:      74600 kB
SUnreclaim:        61488 kB
KernelStack:        5504 kB
PageTables:         7564 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     3418228 kB
Committed_AS:    1898232 kB
VmallocTotal:   34359738367 kB
VmallocUsed:           0 kB
VmallocChunk:          0 kB
AnonHugePages:         0 kB
CmaTotal:          32768 kB
CmaFree:           32552 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
DirectMap4k:       14748 kB
DirectMap2M:     8263680 kB
```



## /proc/slabinfo



##  附录

### 参考资料

* 内核文档 `Documentation/filesystems/proc.txt`
* 
