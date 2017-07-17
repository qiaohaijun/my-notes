@20170714

今天下午在做cublas的Sgemm调用的时候，吃了一个亏.

//![](http://latex.codecogs.com/gif.latex?\\frac{1}{1+sin(x)})

---

在cublasSgemm中间有三个参数
1. lda
2. ldb
3. ldc

cublas的矩阵的参数
- op(A)
- op(B)

---
