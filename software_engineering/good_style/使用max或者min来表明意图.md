#### 使用`std::max`的代码
```cxx
title_max_len = std::max(title_max_len, title_segs.size());
```

#### 使用比较的代码
```cxx
if (title_segs.size() > title_max_len) {
  title_max_len = title_segs.size();
}
```

如果从计算的角度来看, 其实背后没有什么不同. 但是如果从代码的角度来说.

- 使用 `std::max`的代码更加简洁, 同时更容易理解
- 使用for循环是非常传统的代码. 但是时代要求我们要写好的代码, 所以, say goodbye
