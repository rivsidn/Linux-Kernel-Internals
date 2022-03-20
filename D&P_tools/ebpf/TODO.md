## TODO 

* 主要涉及几部分：

  * 如何使用`ebpf`  涉及各种工具
  * `ebpf` 底层实现，内核实现，`JIT` 等
* 系统启动之后`bpftool prog show` 看到的程序是做什么用的？
* 如何获取`tcpdump` 下发的`bpf` 程序？
* GRO、RSS、RPS、XPS、RFS 分别的作用？
* `perf` 工具使用



## 工具汇总

### 编写程序工具

| 工具     | 解释 |
| -------- | ---- |
| c        |      |
| gobpf    |      |
| tracee   |      |
| bcc      |      |
| bpftrace |      |
| bpfilter |      |
| XDP      |      |
| cilium   |      |
|          |      |

### 数据可视化工具

| 工具          | 说明                             |
| ------------- | -------------------------------- |
| eBPF Exporter | ebpf 监控数据导出工具            |
| Prometheus    | 监控报警系统，可以拉取、展示数据 |
| Grafana       | 数据展示工具                     |






## 网站资料

* [eBPF](https://ebpf.io/)
* [Brendan Gregg's Homepage](https://www.brendangregg.com/)
* [Bcc Github](https://github.com/iovisor/bcc)
* [awesome ebpf](https://github.com/zoidbergwill/awesome-ebpf)

> 入门资料：
>
> https://www.ebpf.top/post/ebpf_learn_path/
>
> https://github.com/DavadDi/bpf_study
>
> PPT资料:
>
> https://www.ebpf.top/post/head_first_bpf/
>
> 其他资料：
>
> https://arthurchiao.art/
>
> https://openanolis.cn/sig/sysom/doc/429856194388427432（pingtrace介绍）
>
> 开源项目：
>
> https://github.com/xingfeng2510
>
> https://github.com/aliyun/surftrace



## 代码资料

* 内核bpf C示例程序
* bcc 示例程序

## 视频资料

* [linux内核之旅B站](https://space.bilibili.com/518970180/video)

## 文档资料

* [bcc Python Developer Tutorial](https://github.com/iovisor/bcc/blob/master/docs/tutorial_bcc_python_developer.md)
* [What is eBPF](https://ebpf.io/what-is-ebpf)
* [The BSD Packet Filter](https://www.tcpdump.org/papers/bpf-usenix93.pdf)
* bcc Reference Guide
* BPF Performance Tools
* Systems Performance Enterprise and the Cloud

