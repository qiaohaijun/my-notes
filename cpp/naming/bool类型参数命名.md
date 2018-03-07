```c++
ScopedFlushDenormal::ScopedFlushDenormal() {
  SetDenormalState(/*flush_zero_mode=*/true, /*denormals_zero_mode=*/true);
}

ScopedDontFlushDenormal::ScopedDontFlushDenormal() {
  SetDenormalState(/*flush_zero_mode=*/false, /*denormals_zero_mode=*/false);
}

```

这个代码是`https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/platform/denormal.cc`中的一段.

对于参数为bool类型的函数调用, 可以使用c++的行内注释法.
