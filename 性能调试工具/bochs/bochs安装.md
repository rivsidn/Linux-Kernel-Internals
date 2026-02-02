## 命令安装

```bash
sudo apt-get install bochs
# 安装显示库
sudo apt-get install bochs-x
```





## 源码安装

以 `bochs-2.6.8` 为例。

```bash
./configure --enable-debugger --enable-disasm --enable-instrumentation
make
make install
```



### 编译问题

* 错误信息

  > smm.cc:70:108: error: macro "BX_INSTR_PHY_ACCESS" passed 5 arguments, but takes just 4
  >      BX_NOTIFY_PHY_MEMORY_ACCESS(base, 4, BX_MEMTYPE_WB, BX_READ, BX_SMRAM_ACCESS, (Bit8u*)(&saved_state[n]));

  **修改**

  ```c
  rivsidn@rivsidn:~/Downloads/bochs/bochs-2.6.8$ git diff 
  diff --git a/instrument/stubs/instrument.h b/instrument/stubs/instrument.h
  index 172faba..1288a36 100644
  --- a/instrument/stubs/instrument.h
  +++ b/instrument/stubs/instrument.h
  @@ -119,10 +119,10 @@ void bx_instr_vmexit(unsigned cpu, Bit32u reason, Bit64u qualification);
   #define BX_INSTR_REPEAT_ITERATION(cpu_id, i)  bx_instr_repeat_iteration(cpu_id, i)
   
   /* linear memory access */
  -#define BX_INSTR_LIN_ACCESS(cpu_id, lin, phy, len, rw)  bx_instr_lin_access(cpu_id, lin, phy, len, memtype, rw)
  +#define BX_INSTR_LIN_ACCESS(cpu_id, lin, phy, len, memtype, rw)  bx_instr_lin_access(cpu_id, lin, phy, len, memtype, rw)
   
   /* physical memory access */
  -#define BX_INSTR_PHY_ACCESS(cpu_id, phy, len, rw)  bx_instr_phy_access(cpu_id, phy, len, memtype, rw)
  +#define BX_INSTR_PHY_ACCESS(cpu_id, phy, len, memtype, rw)  bx_instr_phy_access(cpu_id, phy, len, memtype, rw)
   
   /* feedback from device units */
   #define BX_INSTR_INP(addr, len)               bx_instr_inp(addr, len)
  ```

* 错误信息

  > ERROR: X windows gui was selected, but X windows libraries were not found.

  **修改**

  ```bash
  sudo apt-get install libgtk2.0-dev
  ```

* 