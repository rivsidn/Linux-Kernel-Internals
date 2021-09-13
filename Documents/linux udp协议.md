



## 附录

### 客户端获取端口号算法

```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	int low, high;
	int remaining;
	unsigned int rand;
	unsigned short first;

#if 1
        low = 0;
        high = 100;
        remaining = high - low + 1;

        for (i = 0; i < 1024; i++) {
                first = (i * remaining) >> 10; 
                printf("%d\t\t%d\n", i, first);
        }                                                                  
#else
        low = 32768;
        high = 61000;
        remaining = high - low + 1;

        /* 生成一个随机值 */
        rand = random32();
        /* 怎么理解这个处理 */
        first = (((u64)rand * remaining) >> 32) + low;
#endif

	return 0;
}
```





