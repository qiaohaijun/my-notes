python 的语法刚开始的时候觉得比较怪

```python
# self 变量
def foo(self, a, b, c)

# 没有 self 变量的全局函数
def(a, b, c)

```

c++ 虽然没有 this, 但是编译器替我们做了工作, 在我们的函数调用中, 增加了 this 指针.

### this 的用处
1. 为实现对象的链式引用
2. 避免自己给自己赋值
2. 实现一些数据结构, 比如 List
