### 原因
因为我使用了`goto`语句
1. goto语句之后不能声明变量的初始化, 会导致不确定性的行为

### 参考资料
- http://blog.sina.com.cn/s/blog_4b9eab320100s8s1.html

### error输出
```
desm_word_vector_dict_node.cc:299:7: error:   crosses initialization of ‘int vec_dim’
   int vec_dim = dwvdngd->vec_size;
       ^
desm_word_vector_dict_node.cc:298:7: error:   crosses initialization of ‘int vec_cnt’
   int vec_cnt = dwvdngd->vec_count;
       ^
desm_word_vector_dict_node.cc:297:7: error:   crosses initialization of ‘int word_cnt’
   int word_cnt = dwvdngd->word_count;
       ^
desm_word_vector_dict_node.cc:348:3: error: jump to label ‘fail_return’ [-fpermissive]
   fail_return:
   ^
desm_word_vector_dict_node.cc:294:66: error:   from here [-fpermissive]
   if (fwrite(&dwvdngd->vec_count, sizeof(int), 1, fp) != 1) goto fail_return;
                                                                  ^
desm_word_vector_dict_node.cc:308:7: error:   crosses initialization of ‘int word_len’
   int word_len = 0;
       ^
desm_word_vector_dict_node.cc:299:7: error:   crosses initialization of ‘int vec_dim’
   int vec_dim = dwvdngd->vec_size;
       ^
desm_word_vector_dict_node.cc:298:7: error:   crosses initialization of ‘int vec_cnt’
   int vec_cnt = dwvdngd->vec_count;
       ^
desm_word_vector_dict_node.cc:297:7: error:   crosses initialization of ‘int word_cnt’
   int word_cnt = dwvdngd->word_count;
       ^
desm_word_vector_dict_node.cc:348:3: error: jump to label ‘fail_return’ [-fpermissive]
   fail_return:
   ^
desm_word_vector_dict_node.cc:293:67: error:   from here [-fpermissive]
   if (fwrite(&dwvdngd->word_count, sizeof(int), 1, fp) != 1) goto fail_return;
                                                                   ^
desm_word_vector_dict_node.cc:308:7: error:   crosses initialization of ‘int word_len’
   int word_len = 0;
       ^
desm_word_vector_dict_node.cc:299:7: error:   crosses initialization of ‘int vec_dim’
   int vec_dim = dwvdngd->vec_size;
       ^
desm_word_vector_dict_node.cc:298:7: error:   crosses initialization of ‘int vec_cnt’
   int vec_cnt = dwvdngd->vec_count;
       ^
desm_word_vector_dict_node.cc:297:7: error:   crosses initialization of ‘int word_cnt’
   int word_cnt = dwvdngd->word_count;

```
