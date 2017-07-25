简化版的XYZ::Any

带来的好处是可以存放任何类型的数据

```c++
class Any {
 public:
  Any() : content_(NULL) {}

  template<typename ValueType>
  Any(const ValueType &value)  // NOLINT
      : content_(new Holder<ValueType>(value)) {}

  Any(const Any &other)
      : content_(other.content_ ? other.content_->clone() : NULL) {
  }

  ~Any() {
    delete content_;
  }

  template<typename ValueType>
  ValueType *any_cast() {
    return content_ ?
      &static_cast<Holder<ValueType> *>(content_)->held_ : NULL;  // NOLINT
  }

 private:
  class PlaceHolder {
   public:
    virtual ~PlaceHolder() {}
    virtual PlaceHolder *clone() const = 0;
  };

  template<typename ValueType>
  class Holder : public PlaceHolder {
   public:
    explicit Holder(const ValueType &value) : held_(value) {}
    virtual PlaceHolder *clone() const {
      return new Holder(held_);
    }

    ValueType held_;
  };

  PlaceHolder *content_;
};

```
