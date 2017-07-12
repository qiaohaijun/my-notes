正确的调用

```
   cublasSgemm(desm_blas_handle_,
                CUBLAS_OP_N,
                CUBLAS_OP_N,
                100,
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

