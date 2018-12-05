#include <vector>
class foo
{
  public:
    class builder;
    foo(int prop1, bool prop2, bool prop3, std::vector<int> prop4)
      : prop1{prop1}, prop2{prop2}, prop3{prop3}, prop4{prop4}
    { }
    int prop1;
    bool prop2;
    bool prop3;
    std::vector<int> prop4;
};
class foo::builder
{
  public:
    builder& set_prop1(int value) { prop1 = value; return *this; };
    builder& set_prop2(bool value) { prop2 = value; return *this; };
    builder& set_prop3(bool value) { prop3 = value; return *this; };
    builder& set_prop4(std::vector<int> value) { prop4 = value; return *this; };
    foo build() const
    {
      return foo{prop1, prop2, prop3, prop4};
    }
  private:
    int prop1 = 0;
    bool prop2 = false;
    bool prop3 = false;
    std::vector<int> prop4 = {};
};
int main()
{
  foo f = foo::builder{}.set_prop1(5)
                        .set_prop3(true)
                        .build();
}
