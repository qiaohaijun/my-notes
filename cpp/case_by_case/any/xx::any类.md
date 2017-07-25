今天在看dongxu同学写的代码，发现很多用法很有意思，其中就有一个Any类，看的是头昏
原因嘛
1. c++ template 不熟悉

---

```c++

std::any an_object{ std::string("hello world") };
if (an_object.has_value()) {
    std::cout << std::any_cast<std::string>(an_object) << '\n';
}

try {
  std::any_cast<int>(an_object);
} catch(std::bad_any_cast&) {
    std::cout << "Wrong type\n";
}

std::any_cast<std::string&>(an_object) = "42";
std::cout << std::any_cast<std::string>(an_object) << '\n';
```

据说是c++17的标准。

> The class std::any provides a type-safe container to which we can put single values of any type.
