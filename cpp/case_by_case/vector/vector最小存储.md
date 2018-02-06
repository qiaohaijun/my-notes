按 std::vector - cppreference.com 所提供的功能，可以知道实现时最少需要储存：
1. 一个指针
2. 一个表示 capacity 的 size_t （或用指针代表结束位置）
3. 一个表示 size 的 size_t （或用指针代表结束位置）
4. 一个 Allocator 对象

在一般64位平台上，指针和 size_t 都是 8 个字节。
如果 Allocator 少于等于 8 个字节，并且要令其他成员变量做8字节对齐，就会加上 padding。
那么 sizeof 这个类型可能就是 8 × 4 = 32。具体大小是平台相关，不是标准。

作者：Milo Yip
链接：https://www.zhihu.com/question/34955591/answer/60718568
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
