```cxx
std::hash<std::thread::id> hasher;
unsigned long  seed = hasher(std::this_thread::get_id());
```

上面的代码是为了将thread_id转化为一个基本类型的操作.
