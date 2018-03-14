### 注释static函数
```
/*static*/
void getXYZ()
```

简单的注释告诉代码的阅读者, 这个函数是一个静态函数


### 注释bool类型的参数

注释bool类型的参数有很多方法
1. rich type
2. structed wrapper

如果有一些老旧的api呢, 改动代码估计就不是一个容易做到的事情了.

那么注释一下, 至少可以增加一下可读性.

```
 
void foo(/*is_good=*/true,/*is_bad=*/false); 

```
