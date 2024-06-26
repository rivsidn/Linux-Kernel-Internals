**TODO： 继续整理...**

# 可观测性

通过`BPF` 可以实现，分别对：

* 内核函数
* 内核`tracepoint`
* 用户态函数
* 用户态静态定义观测点

的追踪工作，其中我们主要关注前两部分。



## 基本框架

代码按照语言分类，主要分为两部分：

* `C` 程序部分
  * 定义程序执行到探测点时候插入的钩子函数
  * 定义外部通信的通道，向通道中输出内容
* `python` 程序部分
  * 内嵌 `C` 程序
  * 定义程序的探测点，以及探测点对应执行的钩子函数
  * 获取通道中内容，输出到用户态
  * 其他与用户交互的内容，参数解析等



### 基本示例

```python
#! /usr/bin/python

from bcc import BPF
from bcc.utils import printb

# BPF program
prog = """
int hello(void *ctx) {
	bpf_trace_printk("hello world\\n");
	return 0;
}
"""

# load BPF program
b = BPF(text=prog)
b.attach_kprobe(event="ip_rcv", fn_name="hello")

# output
while 1:
    try:
        (task, pid, cpu, flag, ts, msg) = b.trace_fields()
    except ValueError:
		continue
    except KeyboardInterrupt:
        exit()
    printb(b"%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))
```





## 内嵌C程序

### 程序嵌入

### 获取函数参数

### 获取内核信息



## 探测点定义

### 隐式定义

### 绑定kprobe

### 绑定kretprobe

### 绑定tracepoint



## 信道









# 附录

## 参考资料

* [bcc Reference Guide](https://github.com/iovisor/bcc/blob/master/docs/reference_guide.md)
* [bcc Python Developer Tutorial](https://github.com/iovisor/bcc/blob/master/docs/tutorial_bcc_python_developer.md)
* [PT_REGS_PARM macro does not seem to return function arguments in attach_uprobe](https://github.com/iovisor/bcc/issues/3056)

