在深入这个问题之前, 先提几个问题
1. size_t和int有什么区别


### 前言
使用size_t可以提高代码的
1. 可移植性
2. 有效性
3. 可读性

在标准C中有很多函数使用的参数或者返回值都是表示的字节的待续奥
- malloc(n): n指明了需要申请的空间大小
- memcpy(s1,s2,n): n表示要要复制的内存的大小
- strlen(s): 返回值表明了以'\0'结尾的字符串的长度

这些函数的类型就是`size_t`.

```c
void * malloc(size_t n)
void *memcpy(void *s1, void const *s2, size_t n)
size_t strlen(char const *s)
```

size_t 还经常出现在c++标准库中, C++库经常会使用一个相似的类型 size_type

据我所知，大部分的C和C++程序员害怕这些库使用size_t,
因为他们不知道size_t代表什么或者为什么这些库需要使用它,
归根结底,原因在于他们什么时候什么地方需要用到它.

### 可移植性问题
早期的C语言(由Brian Kernighan 和 Dennis Ritchie 在The C Programming Language书中所写，Prentice-Hall, 1978）并没有提供size_t类型.

C标准委员会为了解决移植性问题, 将size_t引入.

#### memcpy为例.

第一次定义API
```c
 void * memcpy(void *s1, void const *s2, int n);
```
1. 使用int类型,在大多数情况下是可以的, 但是不是所有的情况都可以.
2. int 有符号, 可以表示负数, 但是拷贝的数据是不能为负数的. `unsigned int`
3. 在大多数机器上, unsigned int 的最大值比int 大两倍, 比如16位机器, unsigned int 最大值为65535, int的最大值为32767

第二次定义API
```c
void *memcpy(void *s1, void const *s2, unsigned int n);
```

这种情况只能在整形和指针类型具有相同大小的时候好使.


### C数据模型表示法
最近,我偶然发现几篇文章,他们使用简明的标记来表述不同目标平台下c语言数据的实现.
我还没有找到这个标记的来源,正式的语法,甚至连名字都没有,但他似乎很简单,即使没有正规的定义也可以很容易使用起来.
这些标记的一边形式形如：
I nI L nL LL nLL P nP.

其中每个大写字母（或成对出现）代表一个C的数据类型,每一个对应的n是这个类型包含的位数.
I代表int,L代表long,LL代表long long,以及P代表指针（指向数据，而不是函数）.每个字母和数字都是可选的.

例如,I16P32架构支持16位int和32位指针类型,没有指明是否支持long或者long long.
如果两个连续的类型具有相同的大小,通常省略第一个数字.
例如,你可以将I16L32P32写为I16LP32,这是一个支持16位int,32位long,和32位指针的架构.
标记通常把字母分类在一起,所以可以按照其对应的数字升序排列.例如,IL32LL64P32表示支持32位int,32位long,64位long long和32位指针的架构;
然而,通常写作ILP32LL64.  


导致可移植性的根本原因, 就是整形和指针的表示不同.

#### I16LP32架构

整形是 16-bit, 指针类型是32-bit. 摩托罗拉第一代处理器 68000, 处理器的寻址为65535, 但是16bit最大值不够.

所以这个时候, 我们得用`unsigned long` 类型
```c
void *memcpy( void *s1, void const * s2, unsigned long n);
```

这个声明可以用在`IP16`和`IP32`上, 但是在`IP16`上, 使用`unsigned long` 会导致运行变慢

在标准C中规定，长整形（无论无符号或者有符号）至少占用32位，因此在IP16平台上支持标准C的话，那么它一定是IP16L32 平台。
这些平台通常使用一对16位的字来实现32位的长整形。在这种情况下，移动一个长整形需要两条机器指令，每条移动一个16位的块。
事实上，这个平台上的大部分的32位操作都需要至上两条指令。


因此，以可移植性为名将memcpy的第三个参数申明为`unsigned long`而降低某些平台的性能是我们所不希望看到的。
使用size_t可以有效避免这种情况。

size_t类型是一个类型定义，通常将一些无符号的整形定义为size_t，比如说unsigned int或者unsigned long，甚至unsigned long long。
每一个标准C实现应该选择足够大的无符号整形来代表该平台上最大可能出现的对象大小。


### 使用size_t
size_t定义位置
- stddef.h
- stdio.h
- stdlib.h
- string.h
- time.h
- wchar.h

根据规定, size_t是sizeof关键字运算结果的类型.





### link
- http://jeremybai.github.io/blog/2014/09/10/size-t
- http://web.archive.org/web/20101209143037/http://www.eetimes.com/discussion/programming-pointers/4026076/Why-size-t-matters?
