





> obj-$(CONFIG_XFRM) := xfrm_policy.o xfrm_state.o xfrm_hash.o \
> 		      xfrm_input.o xfrm_output.o \
> 		      xfrm_sysctl.o xfrm_replay.o
> obj-$(CONFIG_XFRM_STATISTICS) += xfrm_proc.o
> obj-$(CONFIG_XFRM_ALGO) += xfrm_algo.o
> obj-$(CONFIG_XFRM_USER) += xfrm_user.o
> obj-$(CONFIG_XFRM_IPCOMP) += xfrm_ipcomp.o



| 文件名      | 解释                |
| ----------- | ------------------- |
| xfrm_proc.c | 显示ipsec 统计信息  |
| xfrm_user.c | xfrm 用户态配置接口 |
|             |                     |



## 附录

