



## TODO

* 如何安装软件
  * 如何访问挂载的 iso 文件
  * 如何创建`iso`文件



## 附录

### 创建 iso 文件

```bash
# 生成iso 文件
mkisofs -r -o <file>.iso <path>/
# 挂载iso 文件
sudo mount -o loop <file>.iso
```

### 文件转换工具

```bash
#！ /bin/bash

# 转换成iso之后的目录有两种可能性
# 1.文件转换大小写
# 2.中划线改成下划线
# 3.文件名大于8个的被截断
# 4.后缀大于3个字符的被截断

# 搜集所有的文件，然后依次遍历，查看哪个会被修改，将修改的重新改回来

convert_name=""

function need_convert()
{

}

function filename_convert()
{
	convert_name=;
}

for line in `cat dirs.log`
do
	dir=$(dirname ${line})
	file=$(basename ${line})
	
done
```

