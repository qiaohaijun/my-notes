今天在写cuda代码的时候,发现无法找到cuda.h这个头文件

然后google一下,看看有没有同行遇到过类似的问题
确实有人人遇到过这个问题, 集体学到两个新的cmake 命令

```cxx
find_package(CUDA QUIET REQUIRED)
```

---

```cxx
include_directories(
        /usr/local/cuda/include
)
```



---
clion IDE 因为有自动补齐的功能, 所以对于初学者, 很友好

---
如果要使用 cuda相关的命令, 需要使用

```
find_package(CUDA)
```
来引入cuda相关的命令.

从这里来看, cmake也是由core + package构建的.

---
