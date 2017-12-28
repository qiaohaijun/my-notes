### singleton的多种写法

#### 单线程
```c++
template<typename T>
class Singleton
{
  public:
    static T& getInstance(){
      if(!value){
        value_ = new T();
      }
      return *value_;
    }
  private:
    Singleton();
    ~Singleton();
    static T* value_;
};

template<typename T>
T* Singleton<T>::value_ = NULL;

```

单线程没有什么问题
1. check
2. return
简单,简介


#### 多线程加锁

```c++
template<typename T>
class Singleton
{
  public:
    static T& getInstance(){
      {
        MutexGuard guard(mutex_) //RAII
        if (!value_) {
          value_ = new T();
        }
      }
      return *value_
    }
  private:
    Singleton();
    ~Singleton();
    
    static T* value_;
    static Mutex mutex_;
    
};

template<typename T>
T* Singleton<T>::value_ = NULL;

template<typename T>
Mutex Singleton<T>::mutex_;

```

这个没有问题, 就是有锁的保护, 访问都需要进入临界区, 如果这个是访问频繁的类, 性能就会收到影响.

正确性的问题解决了, 下面要解决的是性能的问题.


#### DCL double-checked locking

```c++
template<typename T>
class Singleton
{
  public:
    static T& getInstance(){
      if(!value_){ // 第一次check的时候不加锁
        MutexGuard guard(mutex_); //第二次create的时候加锁
        if (!value_) {
          value_ = new T();
        }
      }
      
      return *value_;
    }
  private:
    Singleton();
    ~Singleton();
    
    static T* value_;
    static Mutex mutex_;    
};

template<typename T>
T* Singleton<T>::mutex_;

```

第一次见这种写法, 是在java里面, 当时不是很理解为什么要这么啰嗦. 主要是略过了单线程的写法, 以及上锁的写法, 直接给你DCL, 很可能就迷路了. 不知其所以然.

本来以为这个是几乎完美的结局了, 可惜这个DCL是有问题的.

```c++
value_ = new T();
```
原因就是这个代码, 这个代码不是atomic的.

**执行流程A**
1. 分配了一个`T类型`对象需要的内存
2. 在分配的内存处构造`T类型`的对象
3. 把分配的内存的地址赋值给value_;


**执行流程B**
1. 分配了一个`T类型`对象需要的内存
2. 把分配的内存的地址赋值给value_;
3. 在分配的内存处构造`T类型`的对象


这个一个指令是三部执行过程. 
1. step1 是一定最先执行
2. step2, step3的执行顺序不确定. 

>主观上，我们会觉得计算机在会按照1、2、3的步骤来执行代码，但是问题就出在这。
实际上只能确定步骤1最先执行，而步骤2、3的执行顺序却是不一定的。
假如某一个线程A在调用getInstance的时候第12行的语句按照1、3、2的步骤执行，那么当刚刚执行完步骤3的时候发生线程切换，计算机开始执行另外一个线程B。
因为第一次check没有上锁保护，那么在线程B中调用getInstance的时候，不会在第一次check上等待，而是执行这一句，那么此时value_已经被赋值了，就会直接返回*value_然后执行后面使用T类型对象的语句，但是在A线程中步骤3还没有执行！
也就是说在B线程中通过getInstance返回的对象还没有被构造就被拿去使用了！这样就会发生一些难以debug的灾难问题。


**volatile关键字也不会影响执行顺序的不确定性**

>不过在新的C++11中，这个问题得到了解决。
因为新的C++11规定了新的内存模型，保证了执行上述3个步骤的时候不会发生线程切换，相当这个初始化过程是“原子性”的的操作，DCL又可以正确使用了，
不过在C++11下却有更简洁的多线程Singleton写法了，这个留在后面再介绍。

**如何解决out-of-order**

### link
- http://www.cnblogs.com/liyuan989/p/4264889.html
- http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
