C++项目管理
====

### 编译的严谨性
#### 头文件的正确性
C++采用的是"separte compilation"(分离式)编译. 
这个意思是说在编译 foo.cpp的时候, 唯一的对其他依赖代码的要求是,看到它们的头文件(header files).
所以, 只要每次编译时候, 可以确保 foo.cpp 和它的include 的所有头文件一致就可以了. 

但是我们目前并没有做到这一点, 因为
- 一个员工不同时候的编译
- 不同员工的编译
- 不同机器上的编译

在上面三种情况中, 这些header文件可能别其他人修改而无法察觉:
1. linux headers
2. glibc headers
3. gcc headers
4. 3rd headers

alicpp 目的就是解决这个问题.
因为在alicpp环境下编译的时候, 上面说的几种文件, 甚至包括编译器本身, 都是 alicpp git repo中的文件, 这些文件时read only的.

#### 第三方库的菱形依赖问题
MyClass.cpp
```cxx
// MyClass.cpp
#include<a/header.h>
#include<b/header.h>
```

a/header.h
```cxx
//a/header.h
#include<c/header.h>
```



b/header.h
```cxx
//b/header.h
#include<c/header.h>
```

c/header.h
```cxx
// some code 
```

如果 MyClass.cpp 依赖了两个第三方库a和b


### link
- 该文章来自于阿里巴巴技术协会（ATA）精选文章
- https://toutiao.io/posts/155258/app_preview
