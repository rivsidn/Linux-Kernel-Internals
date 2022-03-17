## TODO 

* 为什么通过top 计算CPU利用率不准确？

  实验中例子发现，调度比较忙的时候，通过`top` 计算的`idle` 时间低于`ebpf` 计算的时间利用率大概10% 个百分点。
  
* 主要涉及几部分：

  * 如何使用`ebpf`  涉及各种工具
  * `ebpf` 底层实现，内核实现，`JIT` 等




## 网站资料

* [eBPF](https://ebpf.io/)
* [Brendan Gregg's Homepage](https://www.brendangregg.com/)
* [Bcc Github](https://github.com/iovisor/bcc)



## 文档资料

* [bcc Python Developer Tutorial](https://github.com/iovisor/bcc/blob/master/docs/tutorial_bcc_python_developer.md)
* [What is eBPF](https://ebpf.io/what-is-ebpf)
* bcc Reference Guide
* BPF Performance Tools
* Systems Performance Enterprise and the Cloud

