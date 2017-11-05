现在mxnet 有多种语言的binding

1. python
2. R
3. julia
4. scala

---
### 价值

我觉得将lua对mxnet做binding 是一件非常有意思的事情。

1. lua 的语法
2. mxnet 的效率
3. 是不是可以沟通 torch了

---

### 方法

python 代码我比较熟悉，得益于python的一个lib ，ctypes，python调用c代码是非常简单的。中间的变换，是ctypes来做的。


那么lua 有没有类似的lib来用呢？

``` lua
if(true)
   use it !
else:
   use swigs
end


---
###alien

类似 python 中的 ctypes

---

###cwrap

根据github上的介绍, cwrap 是 torch 用这个工具来将 标准的 c 语言转换为 lua 语言的.




```
