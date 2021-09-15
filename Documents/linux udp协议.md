



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

    low = 0;
    high = 100;
    remaining = high - low + 1;

    //将本来处于[0,1024) 范围内的随机数等比缩小到[0-100) 范围
    for (i = 0; i < 1024; i++) {
        first = (i * remaining) >> 10; 
        printf("%d\t\t%d\n", i, first);
    }

	return 0;
}
```





