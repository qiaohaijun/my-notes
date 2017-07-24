typedef 可以很好地把复杂的代码起一个简单的名字。


```cxx
typedef __gnu_cxx::hash_map<std::string, std::vector<float>, str_hash, str_equal> StrVecMap;
typedef StrVecMap::value_type StrVecMapType;
typedef StrVecMap::iterator hashmapiter;
``` 
