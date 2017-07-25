```c++
int getTop() const {
  return top;
}
```

注意这里的const的关键字，这里的const是用来修饰 getTop() 函数的，表示getTop()这个函数，不会修改类的状态。

> 如果一个函数声明为const，那么指针的类型类似于const class * const ，无论是内存还是内存的值，理论上都是不能修改的


#### 限制
1. 类成员函数
