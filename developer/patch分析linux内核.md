文件是物理单位，`patch`才是真正的逻辑单位。



## patch分析内核步骤

* `patch`搜索

  ```bash
  alias gitlogtime='git log --pretty=format:"%h%x09%ad%x09%an%x09%s" --date=short'
  # 查找文件对应的代码提交记录
  gitlogtime drivers/net/macvlan.c > /home/rivsidn/linux-kernel/macvlan-linux/macvlan.log
  # 获取文件夹对应的提交记录
  gitlogtime drivers/net/ethernet/intel/i40e/
  # 获取代码tag对应的提交记录
  gitlogtime v2.6.22
  ```

  可以将需要关注的提交记录导出到文件中，方便查看。

* `patch`导出

  ```bash
  # patch导出
  git format-patch -1 b863ceb7ddce -o /home/rivsidn/linux-kernel/macvlan-linux
  ```

  `-1` 表示导出当前`patch`，紧随其后的是需要导出的`patch` ID 以及`patch` 导出的目录。

* 导出内核版本

  ```bash
  # 对应git id 之前打tag
  git tag macvlan-init b863ceb7ddce~1
  # 导出对应tag 的文件到指定目录
  git archive --format=tar.gz macvlan-init > /home/rivsidn/linux-kernel/macvlan-linux/macvlan_init.tar.gz
  
  cd /home/rivsidn/linux-kernel/macvlan-linux; mkdir linux
  tar xzvf macvlan_init.tar.gz -C linux/
  ```

* 内核版本Git初始化 

  ```bash
  git init
  git add .
  git commit -a -m "init"
  ```

* 内核中打`patch`

  ```bash
  # patch检查 git自带检查工具
  git apply --check ../0001-NET-Add-macvlan-driver.patch
  # patch检查 patch工具(当patch检查失败的时候显示更加友好)
  patch -p1 --dry-run < ../0001-NET-Add-macvlan-driver.patch
  
  # 打patch git自带工具
  git apply ../0001-NET-Add-macvlan-driver.patch
  # 打patch patch工具
  patch -p1 < ../0001-NET-Add-macvlan-driver.patch
  ```



## 附录

### 内核邮件列表

* [lore kernel org](https://lore.kernel.org/)
* [lkml org](https://lkml.org/lkml)



### 参考资料

* jeff 通过`patch`分析`linux`内核

