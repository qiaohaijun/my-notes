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
  printf("tv_sec:%d\n", tv.tv_sec);
  printf("tv_usec:%d\n", tv.tv_usec);
  printf("tz_minuteswest:%d\n", tz.tz_minuteswest);
  printf("tz_dsttime:%d\n", tz.tz_dsttime);
}
```

测试调用delya()函数所需执行的时间(单位为微妙)

```cxx
#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
 
int delay(int time)
{
    int i,j;
   
    for(i =0;i<time;i++)
        for(j=0;j<5000;j++)
            ;
}
 
int main()
{
  struct  timeval start;
  struct  timeval end;
       
  unsigned  long diff;
  gettimeofday(&start,NULL);
  delay(10);
  gettimeofday(&end,NULL);
  diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
  printf(“thedifference is %ld\n”,diff);
  return 0;     
}
```

说明：

使用该方法就可以检测出调用delay()函数所使用的时间
这个可以说是瑞士军刀


### link
- http://blog.csdn.net/tigerjibo/article/details/7039434
