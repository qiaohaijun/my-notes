
### attribute的用法
```c++

__attribute__((constructor(PRIORITY)))
__attribute__((destructor(PRIORITY)))
```
---

### 设置优先级

``` c++
static  __attribute__((constructor(101))) void before1()
{

    printf("before1\n");
}
static  __attribute__((constructor(102))) void before2()
{

    printf("before2\n");
}
static  __attribute__((constructor(102))) void before3()
{

    printf("before3\n");
}

```
