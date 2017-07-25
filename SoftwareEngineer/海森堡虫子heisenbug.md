```c++
while(iter,hasmoreElements()) {
  Test.ASSERT(iter.nextElement()!=null);
  object obj = iter.nextElement();
  // ......
}

```

ASSERT 中的.nextElement() 调用会有副作用：它会让迭代器改变的是正在读取的元素。


----

这个问题就是一种 海森堡虫子问题

---

# 调试改变了被调试系统的行为
