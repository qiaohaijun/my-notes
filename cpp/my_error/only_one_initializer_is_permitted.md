```
float* ptr_ew_matmul_out_storage = asonpgd->dataflow_b_ew_matmul_out_storage_d_->get_data_ptr();
float*

  ::FloatReduceSum(
      ptr_reduce_sum_out,
      ptr_ew_matmul_out_storage,
      url_embed_dim,
      url_embed_dim,
      url_batch_size,
      context);
  return 0;

```

这个诡异的问题是因为上面我的float*的问题, 没有明确的指出来我的问题.

