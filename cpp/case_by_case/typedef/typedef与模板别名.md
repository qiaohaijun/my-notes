### typedef 无法定义模板类型
```cxx
typedef std::map<std::string, int> map_int_t;
typedef std::map<std::string, std::string> mp_str_t;
```

这两个定义是有问题的, 无法直接使用用`typedef`定义模板别名


c++98/03中的用法为
```cxx
template <typename Val>
struct str_map
{
  typedef std::map<std::string, int> type;
}

str_map<int>::type map1
```

### 参考
- 深入应用c++11
