当只存在`bzImage` 的时候，此时希望能否获取到函数的返汇编，可以通过下列的步骤：

* 将`bzImage` 转换成`vmlinux`，将`vmlinux`反汇编
* 通过`/proc/kallsym` 查询到函数地址，通过地址查询`vmlinux` 的反汇编



### `bzImge`转换`vmlinux`

```bash
# 转换命令，其中的偏移量需要通过后边的命令获取
# 24584 = 24576 + 8
$ dd if=vmlinuz bs=1 skip=24584 | zcat > vmlinux

# 获取偏移量
$ od -A d -t x1 vmlinuz | grep '1f 8b 08 00'
0024576 24 26 27 00 ae 21 16 00 1f 8b 08 00 7f 2f 6b 45

$ dd if=vmlinuz bs=1 skip=12393 | zcat > vmlinux
```

将`vmlinz` 替换成`bzImage` 即可。


### 参考资料

* [Extract vmlinux from vmlinuz or bzImage](https://stackoverflow.com/questions/12002315/extract-vmlinux-from-vmlinuz-or-bzimage)

