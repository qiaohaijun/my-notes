表达式模板Tutorial
====
这个页面主要是来解释mshadow是如何工作的. 在mshadow 背后主要的一个trick是 [Expression Template] 也就是我们常说的表达式模板(http://en.wikipedia.org/wiki/Expression_templates).

我们将要解释这个trick是如何影响编译好的代码的效率. 需要说明的是,表达式模板也是现在主流的C++ 矩阵计算的库背后的trick.

---


如何编写高效的机器学习代码
====

在开始之前, 让我们来思考一个问题. 假设我们想要一个下面的 权重更新规则
```c++
weight =  - eta * (grad + lambda * weight);
```
其中, 权重和梯度是一个长度 ```n```的向量.  我想你之所以选择c++作为你的编程语言,  考虑最多的应该是效率. 这里有个在很多的C/C++ 编程中用到的一个原则:
* 提前申请好需要的内存, **不要在程序运行过程中动态申请内存**


举个例子
```c++
void UpdateWeight (const float *grad, float eta, float lambda,
                   int n, float *weight) {
  for (int i = 0; i < n; ++i) {
    weight[i] =  - eta * (grad[i] + lambda * weight[i]);
  }
}
``` 

这个函数使用提前申请的内存的两个变量```grad```和```weight```. 这样的代码写起来很容易, 但是如果让你一遍又一遍的写这样的代码, 这会是一件很烦人的事情. 所以我们要问的是, 我们可不可以写下面的代码,同时获得刚才举例子中的代码的高效?

```c++
void UpdateWeight (const Vec& grad, float eta, float lambda, Vec& weight) {
  weight = -eta * (grad + lambda * weight);
} 
```
这个问题的答案是 yes, 但是不是那么的显而易见.

A Naive Bad Solution
====

让我们来看看一个非常直接的方法, **运算符重载**

```c++
// Naive solution for vector operation overloading 
struct Vec {
  int len;
  float* dptr;
  Vec(int len) : len(len) { 
    dptr = new float[len];
  }
  Vec(const Vec& src) : len(src.len) {
    dptr = new float[len];
    memcpy(dptr, src.dptr, sizeof(float)*len ); 
  }
  ~Vec(void) {
    delete [] dptr;
  }
};

inline Vec operator+(const Vec &lhs, const Vec &rhs) {
  Vec res(lhs.len);
  for (int i = 0; i < lhs.len; ++i) {
    res.dptr[i] = lhs.dptr[i] + rhs.dptr[i];
  } 
  return res;
} 
```
如果我们增加更多的类似的运算符重载, 我们就可以得到我们想要的结果, 不用写loop循环,直接写一个等式. 但是这样的方式是不高效的. 因为在这个过程中, 有很多的临时内存的申请和释放. 不过我们更好的方法.

让我们换一个方式, 更高效的方式是只重载必要的运算符 ```+=```,```-=```, 这个方法不需要申请临时内存. 但是这个方法会限制我们使用等式的方式

我们在最后来讨论一下, 为什么在C++提供了```move赋值```和```右值引用```的情况下,还要使用表达式模板.

Lazy Evaluation
====
让我们考虑一下为什么我们在计算```operator+```的时候需要申请临时内存.  这是因为我们*不知道* 结果要赋给谁, 如果我们知道, 我们直接将结果写入到相应的内存中, 而不是申请一个临时内存来救急.

如果我们知道最后的target, 下面的代码 ([exp_lazy.cpp](exp_lazy.cpp)) 可以做到不申请临时内存.

```c++
// Example Lazy evaluation code
// for simplicity, we use struct and make all members public
#include <cstdio>
struct Vec;
// expression structure holds the expression
struct BinaryAddExp {
  const Vec &lhs;
  const Vec &rhs;
  BinaryAddExp(const Vec &lhs, const Vec &rhs)
  : lhs(lhs), rhs(rhs) {}
};
// no constructor and destructor to allocate and de-allocate memory,
//  allocation done by user
struct Vec {
  int len;
  float* dptr;
  Vec(void) {}
  Vec(float *dptr, int len)
      : len(len), dptr(dptr) {}
  // here is where evaluation happens
  inline Vec &operator=(const BinaryAddExp &src) {
    for (int i = 0; i < len; ++i) {
      dptr[i] = src.lhs.dptr[i] + src.rhs.dptr[i];
    }
    return *this;
  }
};
// no evaluation happens here
inline BinaryAddExp operator+(const Vec &lhs, const Vec &rhs) {
  return BinaryAddExp(lhs, rhs);
}

const int n = 3;
int main(void) {
  float sa[n] = {1, 2, 3};
  float sb[n] = {2, 3, 4};
  float sc[n] = {3, 4, 5};
  Vec A(sa, n), B(sb, n), C(sc, n);
  // run expression
  A = B + C;
  for (int i = 0; i < n; ++i) {
    printf("%d:%f==%f+%f\n", i, A.dptr[i], B.dptr[i], C.dptr[i]);
  }
  return 0;
}
```

这个思想是我们在遇到```operator+```的时候直接计算结果, 而是返回一个表达式结构[ expression structure],类似编译原理中介绍的AST(abstract syntax tree 抽象语法树), 直到我们遇到重载的```operator=```, 得到最后的target的信息的时候, 我们再做计算,这样就避免了计算过程中临时内存的申请和释放操作!

类似地, 我们可以在```operator=```内定义```DotExp```和延迟求值, 然后将矩阵(向量)乘计算用BLAS来做.


More Lengthy Expressions and Expression Template
====
通过使用延迟求值方法,我们可以避免计算过程中的临时内存的申请. 但是代价是我们能写的代码受到了限制:

* 我们只能写类似```A=B+C```这样长度的代码, 再多一个运算符也不行.
* 当我们需要更多的表达式的时候, 我们需要写更多的```operator=```来满足不同的等式需求.

下面的代码 ([exp_template.cpp](exp_template.cpp))展现了模板编程的魔力, 代码有点长, 但是让你可以写更长的等式.

```c++
// Example code, expression template, and more length equations
// for simplicity, we use struct and make all members public
#include <cstdio>

// this is expression, all expressions must inheritate it,
//  and put their type in subtype
template<typename SubType>
struct Exp {
  // returns const reference of the actual type of this expression
  inline const SubType& self(void) const {
    return *static_cast<const SubType*>(this);
  }
};

// binary add expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template<typename TLhs, typename TRhs>
struct BinaryAddExp: public Exp<BinaryAddExp<TLhs, TRhs> > {
  const TLhs &lhs;
  const TRhs &rhs;
  BinaryAddExp(const TLhs& lhs, const TRhs& rhs)
      : lhs(lhs), rhs(rhs) {}
  // evaluation function, evaluate this expression at position i
  inline float Eval(int i) const {
    return lhs.Eval(i) + rhs.Eval(i);
  }
};
// no constructor and destructor to allocate
// and de-allocate memory, allocation done by user
struct Vec: public Exp<Vec> {
  int len;
  float* dptr;
  Vec(void) {}
  Vec(float *dptr, int len)
      :len(len), dptr(dptr) {}
  // here is where evaluation happens
  template<typename EType>
  inline Vec& operator= (const Exp<EType>& src_) {
    const EType &src = src_.self();
    for (int i = 0; i < len; ++i) {
      dptr[i] = src.Eval(i);
    }
    return *this;
  }
  // evaluation function, evaluate this expression at position i
  inline float Eval(int i) const {
    return dptr[i];
  }
};
// template add, works for any expressions
template<typename TLhs, typename TRhs>
inline BinaryAddExp<TLhs, TRhs>
operator+(const Exp<TLhs> &lhs, const Exp<TRhs> &rhs) {
  return BinaryAddExp<TLhs, TRhs>(lhs.self(), rhs.self());
}

const int n = 3;
int main(void) {
  float sa[n] = {1, 2, 3};
  float sb[n] = {2, 3, 4};
  float sc[n] = {3, 4, 5};
  Vec A(sa, n), B(sb, n), C(sc, n);
  // run expression, this expression is longer:)
  A = B + C + C;
  for (int i = 0; i < n; ++i) {
    printf("%d:%f == %f + %f + %f\n", i,
           A.dptr[i], B.dptr[i],
           C.dptr[i], C.dptr[i]);
  }
  return 0;
}
```
这段代码的主要思想是模板```Exp<SubType>```使用它的派生类作为模板参数, 所以它可以通过```self()```把自己转换为 ```SubType```. ```BinaryAddExp``` 现在是一个可以将表达式组合在一起的一个模板, 类似组合模式. 具体的求值过程通过 function ```Eval```递归地来完成.

* 因为使用了内联(inline), ```operator=```中调用```src.Eval(i)```,在编译过程中会编译为 ```B.dptr[i] + C.dptr[i] + C.dptr[i]```
* 我们可以简化等式的写法, 同时获得loop的效率


Make it more flexible
====

从前面的例子中,我们可以感受到模板编程的灵活性.
最后一个例子很接近```mshadow```, 允许用户自定义二元操作符([exp_template_op.cpp](exp_template_op.cpp)). 

```c++
// Example code, expression template
// with binary operator definition and extension
// for simplicity, we use struct and make all members public
#include <cstdio>

// this is expression, all expressions must inheritate it,
// and put their type in subtype
template<typename SubType>
struct Exp{
  // returns const reference of the actual type of this expression
  inline const SubType& self(void) const {
    return *static_cast<const SubType*>(this);
  }
};

// binary operators
struct mul{
  inline static float Map(float a, float b) {
    return a * b;
  }
};

// binary add expression
// note how it is inheritates from Exp
// and put its own type into the template argument
template<typename OP, typename TLhs, typename TRhs>
struct BinaryMapExp: public Exp<BinaryMapExp<OP, TLhs, TRhs> >{
  const TLhs& lhs;
  const TRhs& rhs;
  BinaryMapExp(const TLhs& lhs, const TRhs& rhs)
      :lhs(lhs), rhs(rhs) {}
  // evaluation function, evaluate this expression at position i
  inline float Eval(int i) const {
    return OP::Map(lhs.Eval(i), rhs.Eval(i));
  }
};
// no constructor and destructor to allocate and de-allocate memory
// allocation done by user
struct Vec: public Exp<Vec>{
  int len;
  float* dptr;
  Vec(void) {}
  Vec(float *dptr, int len)
      : len(len), dptr(dptr) {}
  // here is where evaluation happens
  template<typename EType>
  inline Vec& operator=(const Exp<EType>& src_) {
    const EType &src = src_.self();
    for (int i = 0; i < len; ++i) {
      dptr[i] = src.Eval(i);
    }
    return *this;
  }
  // evaluation function, evaluate this expression at position i
  inline float Eval(int i) const {
    return dptr[i];
  }
};
// template add, works for any expressions
template<typename OP, typename TLhs, typename TRhs>
inline BinaryMapExp<OP, TLhs, TRhs>
F(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
  return BinaryMapExp<OP, TLhs, TRhs>(lhs.self(), rhs.self());
}

template<typename TLhs, typename TRhs>
inline BinaryMapExp<mul, TLhs, TRhs>
operator*(const Exp<TLhs>& lhs, const Exp<TRhs>& rhs) {
  return F<mul>(lhs, rhs);
}

// user defined operation
struct maximum{
  inline static float Map(float a, float b) {
    return a > b ? a : b;
  }
};

const int n = 3;
int main(void) {
  float sa[n] = {1, 2, 3};
  float sb[n] = {2, 3, 4};
  float sc[n] = {3, 4, 5};
  Vec A(sa, n), B(sb, n), C(sc, n);
  // run expression, this expression is longer:)
  A = B * F<maximum>(C, B);
  for (int i = 0; i < n; ++i) {
    printf("%d:%f == %f * max(%f, %f)\n",
           i, A.dptr[i], B.dptr[i], C.dptr[i], B.dptr[i]);
  }
  return 0;
}
```

Summary
=====
到这里, 你应该可以明白它是如何工作的基本原理:

* Lazy evaluation,我们可以看到所有的展开和最后的赋值的结果.
* 模板组合和递归求值, 可以让我们对任意组合的element-wise operations的表达式模板进行求值.
* 由于模板和内联, 我们可以写更新策略的等式, 获得冗长的loop一样的高效:)

所以写机器学习代码的时候,你可以直接写表达式,将你的精力放到算法上面.


The Expression Template in MShadow
=====

在mshadow 中,我们采用了和文中一样的方法, 只是有几个稍微不同的地方:
* 我们将表达式的构建组合与求值分离
     - 没有将 ```Eval```放到 ```Exp```类中. 我们创建了```Plan```类来对表达式进行求值.
     - 这样我们能够在```Plan```中使用更少的变量, 比如,我们可以在求值过程中不需要数组的长度 
     -  一个重要的原因是因为CUDA 的kernel 函数不能使用常量引用的类
     - 这种选择是有争议的,但是至今为止,我们发现这个方法很有用.
* 延迟求值支持复杂的表达式,比如矩阵的点乘
    -  除了 element-wise 表达式, 我们还想支持类似 ```A = dot(B.T(), C)```这样的语法糖.
* 类型检查和数组长度检查

Notes
====
* 表达式模板和C++11: 在C++11中, move 初始化可以被用来避免重复的内存申请, 这个语法可以减少一些表达式模板的使用需求, 但是内存空间依然需要至少申请一次.
   - 这里只是去除了表达式模板的使用,但是存储表达式结果的空间,依然需要提前申请好.
   - 如果我们想要所有的内存都申请好的语法, 同时在计算过程中不需要提前申请内存(这是我们在mshadow中做的), 那么我们还是需要表达式模板.

---
原文:
https://github.com/dmlc/mshadow/tree/master/guide/exp-template
