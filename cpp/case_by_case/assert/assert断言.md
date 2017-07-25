### 简介
断言分为两种类型
1. 动态断言
2. 静态断言

---

### 动态断言
```c++
#include <assert.h>
void assert(int expression);
```
1. assert.h
2. 向stderr 打印一段信息
3. 然后调用abort终止程序运行

---


### 静态断言

> 在新的c++标准中c++0x中，加了对静态断言的支持，引入了新的关键字static_assert来表示静态断言。
使用静态断言，我们可以在程序的编译时期检测一些条件是否成立。

---

### 断言用法总结

**在函数参数合法性检查**
```c++
int resetBufferSize(int nNewSize)
{
//功能:改变缓冲区大小,
//参数:nNewSize 缓冲区新长度
//返回值:缓冲区当前长度
//说明:保持原信息内容不变 nNewSize<=0表示清除缓冲区
assert(nNewSize >= 0);
assert(nNewSize <= MAX_BUFFER_SIZE);
...
}

```
这种写法很清晰，可以不用注释就可以表达自己是用来做参数合法性检查的

---


**一个assert语句检查一个条件**
我看过很多代码，其实很多代码用条件语句将多个条件串联在一起的，这样的问题，就是在出问题的时候，不能马上第一时间的找到问题的所在。


```c++
//   www.169it.com
assert(nOffset>=0 && nOffset+nSize<=m_nInfomationSize); //不好
assert(nOffset >= 0);//好
assert(nOffset+nSize <= m_nInfomationSize);//好
```

这个其实是经验，也是区分高手和新手的一个点，写代码的目的是什么。

---

**assert只做检测，不要产生副作用**
> )不能使用改变环境的语句,因为assert只在DEBUG个生效,如果这么做,会使用程序在真正运行时遇到问题
```c++

assert(i++<100)
//因为如果出错，比如在执行之前i=100,那么这条语句就不会执行，那么i++这条命令就没有执行。

//正确写法
assert(i < 100)

i++;
```
这是因为如果出错，比如在执行之前i=100,那么这条语句就不会执行，那么i++这条命令就没有执行。

---



**assert和后面的语句应空一行,以形成逻辑和视觉上的一致感。**


**有的地方,assert不能代替条件过滤.**
