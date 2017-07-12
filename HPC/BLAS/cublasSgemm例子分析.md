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
Let $\text{S}_1(N) = \sum_{p=1}^N \text{E}(p)$

