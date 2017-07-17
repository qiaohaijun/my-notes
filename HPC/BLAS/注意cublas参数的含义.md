@20170714

今天下午在做cublas的Sgemm调用的时候，吃了一个亏.

![](http://latex.codecogs.com/gif.latex?\\frac{1}{1+sin(x)})

---

在cublasSgemm中间有三个参数
1. lda
2. ldb
3. ldc

cublas的矩阵的参数

- op(A)
- op(B)
- A
- B

---

op 操作说的是是否进行转置, 以及如何转置.


## 提醒
1. 阅读参数解释的时候, 看看参数是和 矩阵 op(A) 有关的, 还是和矩阵 A 有关的.



