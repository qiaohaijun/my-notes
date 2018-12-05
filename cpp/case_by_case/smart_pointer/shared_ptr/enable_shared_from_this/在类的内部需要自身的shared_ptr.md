需求: 在类的内部需要自身的shared_ptr 而不是this裸指针
场景: 在类中发起一个异步操作, callback回来要保证发起操作的对象仍然有效.

另外说一句 你举的例子 毫无实际价值 shared_from_this不是这样玩的.
```c++
shared_ptr<Y> p(new Y);
shared_ptr<Y> q = p->f();
```
