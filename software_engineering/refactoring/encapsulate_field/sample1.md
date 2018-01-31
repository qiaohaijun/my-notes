将仅限于本类使用的变量重写成私有（private）成员变量，并提供访问方法（accessor method）。

这种重构方式可以将与外部调用者无关的变量隐藏起来，减少代码的耦合性，并减少意外出错的概率。

### 重构前

```c++
class SomeClass {
  public:
    int memberA;
  ...
}
```

### 重构后
```c++
class SomeClass {
  private:
    int memberA;
  public:
    int getMemberA();
    void setMemberA(int a);
}

```
