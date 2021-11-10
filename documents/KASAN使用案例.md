通过`KASAN` 定位内核访问越界问题。

越界之后出现的异常可能出现在程序的其他位置，导致这类问题通常难以定位，内核有自带的检测工具`KASAN` 可以用于定位这类问题。



## 内核编译

参照 `lib/Kconfig.kasan` 设置

```
CONFIG_KASAN=y
CONFIG_KASAN_INLINE=y

CONFIG_STACKTRACE=y
```



## 案例

参见 `kernel_samples/kasan`。



**注意：局部变量必须是要memset 之后才能检测到。**

