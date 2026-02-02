


###  addr2line 工具使用

  ```
  ● addr2line 工具使用方法：
  
    基本语法
  
    addr2line -e <带调试信息的可执行文件> <崩溃地址>
  
    实际操作步骤
  
    1. 获取崩溃地址
  
    从你的错误信息中提取关键地址：
    # 从 dmesg 或 crash dump 中找到类似信息：
    # PC is at some_function+0x123/0x456 [module_name]
    # LR is at another_function+0x789/0xabc [module_name]
  
    2. 内核模块调试
  
    # 对于内核崩溃
    addr2line -e vmlinux <崩溃地址>
  
    # 对于驱动模块崩溃
    addr2line -e /path/to/module.ko <相对地址>
  
    3. 用户态程序调试
  
    # 需要带调试符号编译: gcc -g
    addr2line -e ./your_program <崩溃地址>
  
    # 显示函数名和行号
    addr2line -f -C -e ./your_program <地址>
  
    实用选项
  
    -f    # 显示函数名
    -C    # C++ 符号去修饰
    -s    # 显示文件名（简短格式）
    -a    # 显示地址
    -p    # 美化输出格式
  
    针对你的 ARM Phytium 问题
  
    # 1. 首先确保有调试符号的内核
    # 编译内核时启用: CONFIG_DEBUG_INFO=y
  
    # 2. 从崩溃信息获取地址
    # 假设崩溃在 0xffff800008123456
    addr2line -f -C -e vmlinux 0xffff800008123456
  
    # 3. 批量查看多个地址
    echo "0xaddr1 0xaddr2 0xaddr3" | addr2line -f -C -e vmlinux
  
    你可能遗漏的关键点：
    - 必须使用编译时的完全相同的二进制文件
    - 如果是 KASLR（内核地址随机化），需要先计算基地址偏移
    - 对于模块，地址需要减去模块加载基址
  
    超出你预期的建议：
    结合 objdump -d 查看汇编代码上下文，这样能更准确理解崩溃原因：
    objdump -d -S vmlinux | grep -A 10 -B 10 <function_name>
  
  ```
