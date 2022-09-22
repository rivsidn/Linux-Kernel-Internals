## V2.6.35

### 前期准备

```bash
$ git log --pretty=format:"%h%x09%ad%x09%an%x09%s" --date=short  net/core/dev.c > ~/tmp.log
$ for id in $(cat ~/tmp.log | grep 'rps' | cut -d '     ' -f 1); do git format-patch -1 ${id} -o /home/yuchao/linux-kernel/linux-rps/; done;
/home/yuchao/linux-kernel/linux-rps/0001-rps-avoid-one-atomic-in-enqueue_to_backlog.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-Various-optimizations.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-optimize-rps_get_cpu.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-immediate-send-IPI-in-process_backlog.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-consistent-rxhash.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-cleanups.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-shortcut-net_rps_action.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-rps_sock_flow_table-is-mostly-read.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-fixed-missed-rps_unlock.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-keep-the-old-behavior-on-SMP-without-rps.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-add-CONFIG_RPS.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-Fixed-build-with-CONFIG_SMP-not-enabled.patch
/home/yuchao/linux-kernel/linux-rps/0001-rps-Receive-Packet-Steering.patch
$ git checkout -b RPS-annotation 0a9627f2649a~1
$ git branch -m RPS-annotation v2.6.35-RPS-annotation
```

### 功能描述





