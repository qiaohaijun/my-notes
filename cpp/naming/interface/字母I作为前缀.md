c++本身没有`interface`关键字, 所以我们需要在通过约定的方式, 来做一个`人肉编译器`.



```c++
//https://ask.helplib.com/c++/post_876408
class ISerializable
{
public:
 virtual ~ISerializable() = 0;
 virtual void serialize( stream& target ) = 0;
protected:
 void serialize_atomic( int i, stream& t );
 bool serialized;
};
```

上面的例子, 看起来还不错.

