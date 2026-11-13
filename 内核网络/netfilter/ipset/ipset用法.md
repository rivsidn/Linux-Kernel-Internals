
## 创建集合

```bash
ipset create SETNAME TYPENAME [ CREATE-OPTIONS ]
```

| 参数           | 说明           |
|----------------|----------------|
| SETNAME        | 集合名称       |
| TYPENAME       | 集合类型       |
| CREATE-OPTIONS | 创建选项(可选) |


### 集合类型

| 类型     | 说明                   |
|----------|------------------------|
| hash:ip  | hash 表用来存储IP      |
| hash:net | hash 表用来存储netwrok |


