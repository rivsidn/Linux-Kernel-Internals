







## TODO

* 如何安装软件
  * 如何访问挂载的 iso 文件
  * 如何创建`iso`文件



## 附录

### 创建ISO文件

```bash
# 生成iso 文件
mkisofs -r -o <file>.iso <path>
# 挂载iso 文件
sudo mount -o loop <file>.iso /mnt
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

#! /bin/bash

function convert_case()
{
	file=$(echo ${file,,})
}

function convert_underline()
{
	file=$(echo ${file} | sed 's/-/_/g')
}

function convert_cut()
{
	name=$(echo ${file} | cut -d . -f 1)
	suffix=$(echo ${file} | cut -d . -f 2)

	if [ "${name}" == "${suffix}" ];
	then
		suffix=""
	fi

	name=$(echo ${name} | cut -b -8)

	if [ -z ${suffix} ]; then
		file=${name}
	else
		suffix=$(echo ${suffix} | cut -b -3)
		file=${name}.${suffix}
	fi
}

for line in `cat dirs.log`
do
	dir=$(dirname ${line})
	file=$(basename ${line})

	# 大小写字母转换
	convert_case
	# 中划线转下划线
	convert_underline
	# 文件名截取
	convert_cut

	echo ${dir}/${file} ${line}
done
```





```bash
I_138_yuchao@yuchao:~/tmp/filename_convert$ mkisofs --version
mkisofs 2.01 is not what you see here. This line is only a fake for too clever
GUIs and other frontend applications. In fact, this program is:
genisoimage 1.1.11 (Linux)
```

