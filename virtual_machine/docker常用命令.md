
### docker容器提交

```bash
$ docker ps -a 
CONTAINER ID   IMAGE              COMMAND          CREATED         STATUS         PORTS     NAMES
699a025355d6   ubuntu-5.10-i386   "bash -c bash"   6 minutes ago   Up 6 minutes             strange_darwin
$ docker commit 699a025355d6 ubuntu-5.10-i386
sha256:2dc19c4e4b9a9efbcc3e8a9470d84ccc31ba72ac7ea3cfa437208e7810bcd148
```

### docker内文件导出

将文件拷贝到挂载的目录即可.


