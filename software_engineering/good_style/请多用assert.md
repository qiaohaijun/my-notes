assert 翻译成中文的是断言,这个用法很简单,就是来确保满足条件.

对于assert来说,所有的系统都支持

---

assert 是一种编程思想, 可以简化代码的数量, 为何, 如果不满足条件的情况已经被处理了, 那么还需要些那么多代码来处理异常情况吗?

我突然想到了mxnet中的代码中,有大量的CHECK代码,这些代码的目的就是把可能遇到的异常情况都提前处理掉

```cpp
// Always-on checking
#define CHECK(x)                                           \
  if (!(x))                                                \
    dmlc::LogMessageFatal(__FILE__, __LINE__).stream() << "Check "  \
      "failed: " #x << ' '
```

```python
     if not isinstance(handle, ExecutorHandle):
            raise TypeError("Handle type error")
```            
这段python代码本质也是一个assert.   
---

我还是那句话

这是一种编程的思想. 虽然是一个简单的代码,但是他可以带来的帮助是非常大的.
