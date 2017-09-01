### link
- https://zhuanlan.zhihu.com/p/28909947?group_id=886563128056365056

这个算是c++比较高级的知识点.

---


std::move不移动对象

std::forward不转发对象

await_suspend不暂停函数执行

await_resume不恢复函数执行



T&&不一定是右值引用

future<T>不一定在未来给你结果

async也不一定异步

codecvt也不一定真转得对（黑



less<void>不是在比较void的大小

unique_ptr<void>也不一定装着void*

list<T>的allocator分配的不全是T

map的allocator分配的也不全是pair



auto_ptr不auto

any也不是什么都能装

vector也不是向量



vector<bool>里装的不是bool

constexpr不一定编译期执行

auto不一定真如你所想的“自动”

inline也不一定真inline
