
# Linux 2.6.12


- CFLGS_OFF_SLAB 是如何选择slab 存储到哪里的呢？

## 概览图

### slab

```
                        PAGES
               +---------------------+
               |                     |
               |                     |
               |       slab_t        |
               |                     |
               |---------------------|
               |   kmem_bufctl_t     |
               |---------------------|  
               |   kmem_bufctl_t     |
               |---------------------|  
               |   kmem_bufctl_t     |
               |---------------------|  
               |   kmem_bufctl_t     |
               |---------------------|  
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               |                     |
               +---------------------+

```

### off-slab

## 情景分析

### 模块初始化

### 缓存创建

### 缓存申请


# 附录

## TODO

### Linux 2.6.12

- cpuup_callback() 函数中的cache_chain_sem 信号量为什么最后
    ```c
        return NOTIFY_OK;
    bad:
        up(&cache_chain_sem);
        return NOTIFY_BAD;
    ```
    这里如何理解？

- CONFIG_DEBUG_PAGEALLOC 选项
- smp_call_function_all_cpus() 函数实现
