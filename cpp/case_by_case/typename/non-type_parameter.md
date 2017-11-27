non-type parameter(非类型参数)
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

`std::size_t n` 就是非类型参数. 这里要做的不是`类型相关的操作`

