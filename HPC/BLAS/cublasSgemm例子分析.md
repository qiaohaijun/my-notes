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
### fortran 表示法
A(m,n)
1. m表示列
2. n表示行

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
1. 每个vector连续存储, (100,qw_size) 

### small input
1. 全部为1.0 [qw_size,1]

### small_ouput
输出的结果为 []100, 1]

