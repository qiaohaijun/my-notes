这是mxnet 依赖引擎源码分析的第一部分, 主要涉及
1. opr 的基类定义
2. var 的基类定义

代码位置:
```bash
mxnet/src/engine/
```
---

目录下文件的结构:
```bash
[@dl.gitlab.nm.ted engine]# tree
.
├── engine.cc
├── engine_impl.h
├── naive_engine.cc
├── stream_manager.h
├── threaded_engine.cc
├── threaded_engine.h
├── threaded_engine_perdevice.cc
├── threaded_engine_pooled.cc
└── thread_pool.h

0 directories, 9 files

```

(通过 `tree` 命令来获得树状结构)

----
**  `Opr` 定义**

![Opr.png](http://upload-images.jianshu.io/upload_images/22371-ab730c6e74b5b9cb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这个定义的 namespace 是 `mxnet::engine`
```c++
/*! \brief base class of engine operators, used for type checking */
/*! \brief engine operators 的基类, 用来做类型检查 */
struct Opr {
#if ENGINE_DEBUG
  virtual ~Opr() = default;
#endif
  /*!
   * \brief cast variable to derived type T [将variable 转化为派生类型T]
   * \tparam T the type we want to cast into.
   * \return A casted variable.
   */
  template <typename T>
  inline T* Cast();
};  // struct Opr
```

这类是一个基类, 具体的操作需要它的派生类来处理.

```c++
// implementation of the inline functions
template <typename T>
inline T* Var::Cast() {
  static_assert(std::is_base_of<Var, T>::value,
                "must inherit `mxnet::engine::Var`");
#if ENGINE_DEBUG
  return dynamic_cast<T*>(this);
#else
  return static_cast<T*>(this);
#endif
}
```
Var::Cast 的具体实现
1. 类型检查, 这里用的static_assert, 这个是c++0x 以后提出的特性, 在编译期间做
2. 根据是否 `DEBUG` 采用不同的 cast 操作

---
**Var**

![var.png](http://upload-images.jianshu.io/upload_images/22371-e10eff5cab4af939.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c++
/*! \brief base class of engine variables, used for type checking */
/*! \brief engine variables 的基类, 和 Opr 一样是用来做类型检查的 */
struct Var {
#if ENGINE_DEBUG
  virtual ~Var() = default;
#endif  // ENGINE_DEBUG
  /*!
   * \brief cast variable to derived type T
   * \tparam T the type we want to cast into.
   * \return A casted variable.
   */
  template <typename T>
  inline T* Cast();
};  // struct Var

```
如同 `Opr` 一样, 这个也是基类啊, 也是做了两件事
1. 类型检查, 妥妥的防御性编程, 多多排查, 能在编译期间检查出来问题的, 就不要拖到运行时了
2. 变身, 我要变成子类.

```c++
// implementation of the inline functions
template <typename T>
inline T* Var::Cast() {
  static_assert(std::is_base_of<Var, T>::value,
                "must inherit `mxnet::engine::Var`");
#if ENGINE_DEBUG
  return dynamic_cast<T*>(this);
#else
  return static_cast<T*>(this);
#endif
}
```

---






参考
http://www.jianshu.com/p/92224237fac9
