c++11 支持的语法

```cxx
dict_->cpu_hash_[my_word] = my_word_vec_info;
```

但是这个语法在使用std=gpu++0x的时候是报错的
```bash
desm_word_vec_dict.cpp:137:43: error: ‘struct std::pair<int, int>’ has no member named ‘index’
         std::cout << "[xx]" << it->second.index << std::endl;
                                           ^
desm_word_vec_dict.cpp:138:43: error: ‘struct std::pair<int, int>’ has no member named ‘vec_cnt’
         std::cout << "[xx]" << it->second.vec_cnt << std::endl;
```
