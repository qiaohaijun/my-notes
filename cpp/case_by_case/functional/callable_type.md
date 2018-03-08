Callable type指可以像调用函数一样被调用的对象或函数，包括：

- std::function
- std::bind
- std::result_of
- std::thread::thread
- std::call_once
- std::async
- std::packaged_task
- std::reference_wrapper


根据C++ 17 Standard，所有Callable type都可以通过std::invoke方法进行显式调用。

