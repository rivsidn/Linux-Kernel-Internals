

| 字符 | 选项            | 说明                 |
|------|-----------------|----------------------|
| f    | SLAB_DEBUG_FREE |                      |
| z    | SLAB_RED_ZONE   |                      |
| p    | SLAB_POISON     |                      |
| u    | SLAB_STORE_USER |                      |
| t    | SLAB_TRACE      |                      |
| a    | SLAB_FAILSLAB   |                      |
| o    | X               |                      |
| -    | X               | 禁止所有内核调试信息 |


## SLAB_DEBUG_FREE

```c
#define SLAB_DEBUG_FLAGS (SLAB_RED_ZONE | SLAB_POISON | SLAB_STORE_USER | \
			  SLAB_TRACE | SLAB_DEBUG_FREE)

#define DEBUG_DEFAULT_FLAGS (SLAB_DEBUG_FREE | SLAB_RED_ZONE | \
				SLAB_POISON | SLAB_STORE_USER)
```




```c

//默认调试选项
#define DEBUG_DEFAULT_FLAGS (SLAB_DEBUG_FREE | SLAB_RED_ZONE | \
				SLAB_POISON | SLAB_STORE_USER)

		switch (tolower(*str)) {
		case 'f':
			slub_debug |= SLAB_DEBUG_FREE;
			break;
		case 'z':
			slub_debug |= SLAB_RED_ZONE;
			break;
		case 'p':
			slub_debug |= SLAB_POISON;
			break;
		case 'u':
			slub_debug |= SLAB_STORE_USER;
			break;
		case 't':
			slub_debug |= SLAB_TRACE;
			break;
		case 'a':
			slub_debug |= SLAB_FAILSLAB;
			break;
		case 'o':
			/*
			 * Avoid enabling debugging on caches if its minimum
			 * order would increase as a result.
			 */
			disable_higher_order_debug = 1;
			break;
		default:
			pr_err("slub_debug option '%c' unknown. skipped\n",
			       *str);
		}
```


