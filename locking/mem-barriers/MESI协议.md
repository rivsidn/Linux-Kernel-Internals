

| 数据状态  | 内容有效 | 独占 | 写回内存 |
| --------- | -------- | ---- | -------- |
| modified  | 是       | 是   | 是       |
| exclusive | 是       | 是   | 否       |
| shared    | 是       | 否   | 否       |
| invalid   | 否       | X    | X        |





| 触发事件               | 描述                     |
| ---------------------- | ------------------------ |
| 本地读取(Local read)   | 本地CPU读取本地cache数据 |
| 本地写入(Local write)  | 本地CPU写入本地cache数据 |
| 远端读取(Remote read)  | 其他CPU读取本地cache数据 |
| 远端写入(Remote write) | 其他CPU写入本地cache数据 |



```
/*
 * 通过smp_wmb() 确认之前初始化的值(v)在赋值给(p)之前已经被完整写入，确保通过
 * (p) 获取到的数据的一致性.
 */

```







## 附录

### 参考资料

* [CPU缓存一致性协议MESI](https://www.cnblogs.com/yanlong300/p/8986041.html)