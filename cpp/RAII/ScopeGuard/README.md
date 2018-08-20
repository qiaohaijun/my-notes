早在 2000 年 Andrei Alexandrescu 就提提到 ScopeGuard，dismiss 是 Andrei 原始设计的一部分。是为了支持 rollback, 比如：
```c++
auto onFailureRollback = clover::MakeScopeGuard([&] { /* rollback */ });
// do something 
onFailureRollback.dismiss();
```
这样 do something 中任何地方发生异常，都会调用 rollback。

当 do something 成功了，就可以撤销掉 rollback。但我移植时删除掉了 MakeScopeGuard 函数。 

“另外 ScopeGuard 可以将模板参数的 Fun 类型作为基类” 
不要停留在设想，你自己试着按照这个思路实现，看看有没有什么问题。
你也可以删除掉 _active，试试有什么问题。这个 ScopeGuard 所有函数都是内联的，编译器会自动优化。空基类优化之类，在这里根本没有意义。
