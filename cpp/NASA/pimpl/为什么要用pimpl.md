pimpl的目的是实现"类的接口和实现"进行解耦.

1. 可以避免在头文件里保留私有细节
2. 这个方法可以促进API接口与实现完全分离的重要机制.

---
pimp 也不是严格意义上的设计模式, 因为受限于C++的特定限制.

```c++
// foo.h

class foo {
  public:
    Function1();
    Function2();
  protected:
    Function3();
  private:
    Impl* pimpl;
}

```


```c++
// foo.cc
class foo {
  public:
    PrivateFunction1();
    PrivateFunction2();
    PrivateData1;
    PrivateData2;
    
}

```


### 优点

1. 降低耦合
2. 信息隐藏
3. 降低编译依赖, 提高编译速度
4. 接口和实现分离.


---

### 举例说明

#### 需求

设计一个书籍类Book, Book包含目录属性, 并提供打印数据内部信息的对外接口, 设计如下.

```c++

class Book {
  public:
    void print();
  private:
    std::string m_Contents;
}
```
这个是没有使用PIMP手法的代码, 用户知道 `print()`就可以使用 Book类.

#### 需求变化了

需要更多的信息出来, 打印出来书籍的标题属性.

```c++
class Book {
  public:
    void print();
  private:
    std::string m_Contents;
    std::string m_Title;
}

```

虽然使用print()接口仍然可以直接输出书籍的信息,但是Book类的使用者却不得不重新编译所有包含Book类头文件的代码.
为了隐藏Book类的实现细节，实现接口与实现的真正分离, 以使用Pimpl方法.


#### BookImpl实现
```c++
// publich

#pragma once

class Book{
  public:
    Book();
    ~Book();
    void print();
  private:
    class BookImpl; // Book实现类的前置声明
    BookImpl* pimpl;
  
}
```

对外的头文件public.h 只包含Book类的外部接口, 将真正的实现细节被封装到 BookImpl类. 
为了不对外暴露 BookImpl类. 将其声明为Book类的内部类, private

```c++
// private.h
#pragma once

#include "public.h"
#include <iostream>

class Book::BookImpl
{
  public:
    void print();
  private:
    std::string m_Contents;
    std::string m_Title;   
}

```

private.h 将具体的实现全都包含了.

```c++

#include "private.h"
#include "public.h"

Book::Book()
{
  pimpl = new BookImpl();
}

Book::~Book() {
  delete pimpl;
}

void Book::print()
{
  pimpl->print();
}

/*
 *  BookImpl 类的实现函数
 */



void Book::BookImpl::print()
{
  std::cout << "print from BookImpl" << std::endl;
}

```

#### 用法
```c++
#include "public.h"

int main() {
  Book book;
  book.print();
  return 0;
}
```

#### handle class
像Book类这样使用Pimpl的类，往往被称为handle class

#### implementation class
BookImpl类作为实现类，被称为implementation class

由于Pimpl解除了接口与实现之间的耦合关系，从而降低文件间的编译依赖关系，Pimpl也因此常被称为 "编译期防火墙"




---



### 作为编译防火墙




### link
- http://blog.csdn.net/lihao21/article/details/47610309

