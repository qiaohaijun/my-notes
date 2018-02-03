### enum的问题
因为enum是c语言的老物件, 必须得兼容c语言的语法和语义.

c没有namespace的概念.


```c++
enum FileAcess {
  Read = 0x1,
  Write = 0x2,
};

```

你猜猜, 你如果想要引用, `Read`和 `Write`, 你是不是觉得

```c++
FileAcess::Read
FileAcess::Write
```

哈哈, 你错了, 应该这么用

```c++
::Read
::Write
```

```c++
class FileAccess { 
  static const int Read = 0x1; 
  static const int Write = 0x2; 
}; 
```



---
没办法, 谁让c语言本身没有namespace的意思.

这个其实对于小规模的程序内有啥影响, 但是对于大规模的程序, 问题就麻烦了. 

其实这么定义就可以了.

```c++
enum FileAccess{
  Read = 0x1,
  Write = 0x2,
};

enum FileShare{
  Read = 0x1, // 重定义
  Write = 0x2, // 重定义
};

搞不定了吧, 没关系


```c++
class FileAccess { 
  static const int Read = 0x1; 
  static const int Write = 0x2; 
}; 
```

```

---



### 举例子

#### strong_enum 的例子

```c++
enum class TrafficLight{
  RED,
  YELLOW,
  GREEN
};
```
