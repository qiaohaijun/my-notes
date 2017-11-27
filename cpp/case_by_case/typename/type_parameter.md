 type parameter (类型参数)
 ===
 
 ```cpp
 template<typename T,           // template for n x n matrices of
         std::size_t n>        // objects of type T; see below for info
class SquareMatrix {           // on the size_t parameter
public:
  ...
  void invert();               // invert the matrix in place
};

```

这段代码中的`typename T`就是类型参数, 也是我们最常见的模板的用法.
