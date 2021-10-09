以`2.6.35.6` 内核 igb 驱动为例，讨论内核收包。



## 中断

```c
//一般我们的中断模式都是msix，所以此处以msix 举例
static int igb_request_msix(struct igb_adapter *adapter)
{
    for () {
		//挂载中断处理函数
        err = request_irq(adapter->msix_entries[vector].vector,
                         igb_msix_ring, 0, q_vector->name,
                         q_vector);
        if (err)
            goto our;
    }
}

//中断处理函数
static irqreturn_t igb_msix_ring(int irq, void *data)
{
    struct igb_q_vector *q_vector = data;
    
    /* Write the ITR value calculated from the previous interrupt. */
    igb_write_itr(q_vector);
    
    napi_schedule(&q_vector->napi);
    
    return IRQ_HANDLED;
}

//中断处理函数最终会调用到该函数，该函数主要做了两个动作
//1. 将这个napi 结构体加入到 sd->poll_list 中
//2. 触发软中断
static inline void ____napi_schedule(struct softnet_data *sd,
                                    struct napi_struct *napi)
{
    list_add_tail(&napi->poll_list, &sd->poll_list);
    __raise_softirq_irqoff(NET_RX_SOFTIRQ);
}
```



中断触发后的代码流程如上所示，最终会将 napi 结构体加入到 `sd->poll_list` 中并触发软中断。



## 软中断

 软中断触发之后会进入到`net_rx_action()` 中。

```c
static int __init net_dev_init()
{
    //挂载收包软中断处理函数
    open_softirq(NET_RX_SOFTIRQ, net_rx_action);
}

static void net_rx_action(struct softirq_action *h)
{
    while () {
        if () {
            //此处会调用igb_poll() 函数
            work = n->poll(n, weight);
            trace_napi_poll();
        }
    }
}
```



软中断处理过程中会有数量限制，防止内核一直陷到软中断处理中。

此处的数量限制有两层，执行`net_rx_action()` 函数中有处理报文数量限制，执行 `igb_poll()` 有处理报文数量限制。



## 驱动收包函数





## TODO

* 中断中调用软中断的代码
* 中断调用软中断过程中，是什么时候允许中断的？
* 调度是何时发生的？
* 软中断中是否允许调度？
* 中断之间映射关系？
* 中断、调度、软中断
* 
* `netif_rx()`与`netif_receive_skb()` 这两个函数之间什么差异？
* 
* 


