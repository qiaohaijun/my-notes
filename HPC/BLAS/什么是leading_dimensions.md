## 引出问题


在学习CUDA的矩阵运算当中，如果定义了M*N的矩阵A，都会有一个相应的参数ldA，也就是A的leading dimensions，但是一直搞不懂是哪个数，例如3*2维矩阵

```
1 2
3 4
5 6
```

### 问题
1 什么是leading dimensions


---

```
cublasStatus_t cublasSetMatrix(int rows, int cols, int elementSize,const void *A, int lda, void *B, int ldb);
```

> 这些参数大部分看名字就知道什么意思了，其中lda和ldb指明了源矩阵A和目的矩阵B的主维度（leading dimension），所谓主维就是矩阵的行总数, 这个参数只在需要> host矩阵一部分数据的时候很有用. 
> 也就是说，当需要完整的矩阵时，lda和ldb都应该是M。

---

> leading dimensions你可以理解为矩阵的第一维，比如你上面的矩阵，ldA=3。
> 需要注意的是：CUBLAS排列矩阵的方式是列优先，不同于一般C语言行优先原则


---


leading dimension 就是主维度.
