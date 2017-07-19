### class 与struct的区别
只有数据权限不同
1. struct 默认 public
2. class 默认 private

---

### 规范
人为增加语义, struct 作为数据存储.

```cxx
DesmWordVectorDictNodeGlobalData::DesmWordVectorDictNodeGlobalData() :
    vec_array_(NULL), data_holder_(NULL), word_len_(NULL), vec_count(0), vec_size(0),
    norm_vec(NULL), relu_vec(NULL), zero_vec(NULL), default_idx_(-1), zero_idx_(-1) {
  return;
}

```
