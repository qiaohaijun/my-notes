### 前提
1. CPU的乱序执行
2. C++11之前的内存模型
3. pthread_once API

----



### why DCL not work
我的体会是，搞多线程编程如履薄冰，千万别自己发明东西，那将几乎肯定是错的。不说别的，单是一个 Singleton 模式的线程安全实现就能难倒很多人。一度人们认为 Double checked locking 是王道，兼顾了效率与正确性。后来有神牛指出由于乱序执行的影响，DCL 是靠不住的。（这个又让我想起了 SQL 注入，十年前用字符串拼接出 SQL 语句是 Web 开发的通行做法，直到有一天有人利用这个漏洞越权获得并修改网站数据，人们才幡然醒悟，赶紧修补。）Java 开发者还算幸运，可以借助内部静态类的装载来实现。C++ 就比较惨，要么次次锁，要么 eager initialize、或者动用 memory barrier 这样的大杀器（ http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf ）。接下来 Java 5 修订了内存模型，并增强了 volatile 的语义，这下 DCL (with volatile) 又是安全的了。然而 C++ 的内存模型还在修订中，C++ 的 volatile 目前还不能（将来也难说）保证 DCL 的正确性（只在 VS2005+ 上有效）。

----
### Code
```cxx
SDNN * SDNN::instance()
{   
    // Double-Checked Locking
    if (instance_ == NULL)
    {   
        pthread_mutex_lock(&instance_mutex_); 
        if (instance_ == NULL)
            instance_ = new SDNN();
        pthread_mutex_unlock(&instance_mutex_); 
    }
    return instance_;
}
```

----

### link
- https://book.douban.com/review/2919204/
- C++ and the Perils of Double-Checked Locking
- http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
