最近在整理tensorflow serving的源码, 从中学到不少东西, 本文就是一个例子.


```cxx
// servable_handle.h
template <typename T>
class ServableHandle {
 public:
  static_assert(!std::is_pointer<T>::value,
                "Servables are implicitly passed as pointers, please use T "
                "instead of T*.");

  /// ServableHandle is null by default.
  ServableHandle() = default;

  const ServableId& id() const { return untyped_handle_->id(); }

  // Smart pointer operations.

  T& operator*() const { return *get(); }

  T* operator->() const { return get(); }

  T* get() const { return servable_; }

  operator bool() const { return get() != nullptr; }

  // See the end of this file for comparison operators, which must be declared
  // at namespace scope to support left-hand-side arguments of different types.

 private:
  friend class Manager;

  explicit ServableHandle(std::unique_ptr<UntypedServableHandle> untyped_handle)
      : untyped_handle_(std::move(untyped_handle)),
        servable_(untyped_handle_ == nullptr
                      ? nullptr
                      : untyped_handle_->servable().get<T>()) {}

  std::unique_ptr<UntypedServableHandle> untyped_handle_;
  T* servable_ = nullptr;
};


```

---

这个算是技术, 因为c++到现在还不支持 `concept`, 这种方法可以从一定程度上来模拟一下`concept`.

这个比较粗糙, 暂时能够用来做的约束是使用 `<type_trait>`

---
