何时向 `hash2` 中添加东西？

何时创建`socket`？









## TODO

* `udp_table{}` 结构体中，两个hash 表的关系

  ```c
  struct udp_table {
      struct udp_hslot	*hash;
      struct udp_hslot	*hash2;
      unsigned int 		mask;
      unsigned int		log;
  }
  ```

  

* 