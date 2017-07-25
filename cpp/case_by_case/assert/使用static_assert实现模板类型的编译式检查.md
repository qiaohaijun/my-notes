使用static_assert实现模板类型的编译式检查
==== 

assert 是一个断言信息，c++提供了两种
1. assert 用来在运行时检查
2. static_assert 是编译器检查

```c++
assert(true);
static_assert(true, "will do nothing");
assert(false); // assert宏：运行时断言，将打印一条出错（含cpp文件名、行号）信息并强制终止程序运行
static_assert(false, "make a error message"); // 产生一个编译时错误，并提供给定的错误信息：error C2338: make a error message
```

----

从颜色上可以分辨：static_assert貌似是C++关键字？而assert是一种自定义类型（带参数的宏）

### type traits 是一些class，在编译时候提供了类型的信息
<type_traits>
在头文件<type_traits>可以找到

```c++
// 同时使用static_assert与type traits实现模板类型编译时检查
template <typename T1, typename T2>
auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
{
	// 确保T1、T2的类型是integral，否则触发编译器报错
	static_assert(std::is_integral<T1>::value, "Type T1 must be integral");
	static_assert(std::is_integral<T2>::value, "Type T2 must be integral");

	return t1 + t2;
}

void test()
{
	std::cout << add(1, 3.14) << std::endl;  // error C2338: Type T2 must be integral
	std::cout << add("one", 2) << std::endl; // error C2338: Type T1 must be integral

	auto r = add(3L, '2');			 // ok! long、char都属于整型
	// typeid用于运行时类型检查，而type traits则是编译时判断
	std::cout << typeid(r).name() << std::endl; // long
}
```

使用static_assert实现模板类型的编译式检查
