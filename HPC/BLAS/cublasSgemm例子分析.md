正确的调用

```
   cublasSgemm(desm_blas_handle_,
                CUBLAS_OP_N,
                CUBLAS_OP_N,
                100, // number of rows of matrix op(A)
                1,
                my_query_word_size,
                &alpha,
                ptr_d_query_workspace_big_input,
                100,
                ptr_d_query_workspace_small_input,
                my_query_word_size,
                &beta,
                ptr_d_query_workspace_small_output,
                100

    );
```

---

### 函数原型 

C = alpha * op(A) * op(B) + beta * C

- alpha 是scalar
- beta 是 scalar
- A 矩阵
- B 矩阵
- C 矩阵

---

- op(A)的shape => (m,k)
- op(B)的shape => (k,n)
- C的shape => (m,n)

---

- A的指针 `ptr_d_query_workspace_big_input`
- B的指针 `ptr_d_query_workspace_small_input`
- C的指针 `ptr_d_query_workspace_small_output`

#### big_input
使用列表示法如下
- 每个vector连续存储, (100,qw_size) 
- 100 表示一个列向量的大小
- qw_size 表示多少个列向量
 
使用c语言二维矩阵表示法
- A[qw_size][100]
对于熟悉C的程序员, 这个不用多解释


### small input
1. 全部为1.0 (qw_size,1)

### small_ouput
输出的结果为 (100, 1)

---

### 为了方便记忆, 做一下规定
1. fortran表示法为(column_size, row_size)表示shape
2. c语言表示法使用A[row_size][column_size]表示shape


