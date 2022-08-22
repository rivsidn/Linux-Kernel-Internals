

* `ip_proto_bind()` 做了什么？
* `ip_proto_accept()`？
* 
* `tcp_write_wakeup()`
* `tcp_sequence()`
  * `delay_acks`作用？
* `tcp_header{}` 中为什么这么安排？
* 协议中的各种`seq` 怎么理解？
* `tcp_conn_request()`
  * 发送的`syn/ack` 报文何时释放
  * 放到`rqueue` 中的报文如何处理，是否还有其他放到`rqueue` 中的报文
* `release_sock()`
* `reset_timer()`
* `net_timer` 的作用？
  * 为什么在这里设置`KEEPOPEN` 计时器
* `tcp_read_wakeup()`、`tcp_write_wakeup()` 作用？
* 报文中的`syn`和`ack` 发送机制





0.98-annotation





## 附录

### TODO

* `verify_area()` 作用？
* `memcpy_fromfs()`作用？
* `ip` 协议
* `ip` 路由

