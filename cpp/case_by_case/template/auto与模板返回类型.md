auto配合decltype，可以解决一些以前可能需要很丑的解法

### 问题描述
```cxx
template <class T, class　U>
??? mul(T x, U y)
{
  return x*y;
}
```
由于`x`和`y`是参数, 返回的是`x*y`的类型, 如何得到`x*y`的类型.



### c++11 以前

1. 使用`decltype`和`0`
2. 转化为指针
3. 再取指针


```cxx
template<class T, class U>

decltype(*(T*)(0) * *(U*)(0)) mul(T x, U y)
{
  return x*y;
}
```

如果不能用这个trick就完蛋了.

### c++11
这里有一个解决方案`auto`+`decltype`

属于 `auto` 的特殊用法. **占位符**

```cxx
template<class T, class U>
auto mul(T x, U y) ->decltype(x*y)
{
  return x*y;
}
```

### c++14

Thanks to C++14, auto在C++14可以作为函数返回类型了，于是你可以直接这样了
```cxx
auto mul(T x, U y)
{
  return x*y;
}

```


### link
- https://www.zhihu.com/question/35517805
