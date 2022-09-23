## V2.6.35

### 前期准备

```bash
# 获取内核提交
git log --pretty=format:"%h%x09%ad%x09%an%x09%s" --date=short  net/core/dev.c | grep rfs
# 生成分支
git checkout -b RFS-annotation fec5e652e58f~1
# 检查patch
git apply --check 0001-rfs-Receive-Flow-Steering.patch
# 应用patch
git apply 0001-rfs-Receive-Flow-Steering.patch
```



```
#相关提交
fec5e652e58f	2010-04-16	Tom Herbert	rfs: Receive Flow Steering
```



