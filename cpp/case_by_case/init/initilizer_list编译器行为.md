### initializer_list

C++11 为了统一初始化语法, 引入了 `initializer_list`类型, 表示一个同构的值序列, 所以你可以写下面的代码

```c++
foo(std::initializer_list<int> list);
foo({1,2,3})
foo({4})
```
编译器会自动的把大括号内的值封装为一个 `initializer_list`.
当然我们可以让构造函数接受 `initializer_list`作为它的参数
```c++
class IntVector {
public:
    IntVector(initilizer_list<int> list);
}
IntVector iv = {1,2,3};
```


这种构造函数叫做 initializer-list constructor（这个名称我从 C++11FAQ 中得知，应该是通用的术语）这种构造函数的优先级要高于普通的构造函数。

所以如果我们还有另外一个构造函数：

```c++
class IntVector {
public:
    IntVector(int a, int b);
    IntVector(initilizer_list<int> list);
}
```

IntVector iv = {1, 2} 这条语句调用的是initializer-list constructor。


### 参考
- http://blog.guorongfei.com/2016/03/09/cppx-list-initilization/
