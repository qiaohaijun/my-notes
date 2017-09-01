这个名字确实有点`随性`

### include
**sys/time.h**

---

### 源码

```c
struct  timeval{
  long  tv_sec;   //秒
  long  tv_usec;  //微秒
};
```
例子

```c
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
 
int main()
{
        struct  timeval    tv;
        struct  timezone   tz;
        gettimeofday(&tv,&tz);
 
        printf(“tv_sec:%d\n”,tv.tv_sec);
        printf(“tv_usec:%d\n”,tv.tv_usec);
        printf(“tz_minuteswest:%d\n”,tz.tz_minuteswest);
        printf(“tz_dsttime:%d\n”,tz.tz_dsttime);
}
```
这个可以说是瑞士军刀


### link
- http://blog.csdn.net/tigerjibo/article/details/7039434
