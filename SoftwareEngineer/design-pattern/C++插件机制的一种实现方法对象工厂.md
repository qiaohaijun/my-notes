## 背景
在我们的实际开发过程中，经常会开发一些插件，比较常见的例子如：
给你 DataHandler，它是一个抽象类，提供一些数据操作的接口，
然后插件开发者就需要继承DataHandler，并按需求实现对应的接口，将其作为插件，
编译到最终的二进制程序中，最后通过配置文件指定生效该插件


---

```c++
//  data_handler.h
 
Class DataHandler {
 
public:
 
virtual bool Handle(std::vector<Data*> data_list) =0;
 
virtual ~DataHandler(){}
 
};
 
REGISTER_REGISTER(DataHandler)
#define REGISTER_DATA_HANDLER(name) REGISTER_CLASS(DataHandler, name)
```

---

```c++
// my_data_handler.h
 
class MyDataHandler : public DataHandler {
 
public:
 
virtual bool Handle(std::vector<Data*> result_list);
 
};
```

---

```c++
// my_data_handler.cc
 
bool MyDataHandler::Handle(std::vector<Data*> data_list) {
 
// Implemention...
 
}
REGISTER_DATA_HANDLER(MyDataHandler)
```

```c++
// configure file
 
DataHandler{
 
name : MyDataHanlder,
 
prior   : 1
 
}
 
DataHanlder{
 
name : YourDataHandler,
 
prior   : 1
 
}
```

---

此时你只需把你的MyDataHandler编译为动态库或者是静态库，并链接到最终二进制中，在数据处理时就会调用你的DataHandler。是不是很方便开发哈，这就是所谓的插件开发思想。下面主要介绍下具体的实现。

---

### 实现思想
想要实现上述功能的插件框架，主要从以下几个方面着手解决：

http://yaronspace.cn/blog/archives/1500/register

#### 如何组织不同类型的插件
如目前有DataHanlder，但是系统可能也支持ServiceHanlder等等；某类插件可能包含多个具体的实例的插 件，那又如何组织；这里很容易就想到了双层map的数据结构，如下图所示，每层Map的Key都插件类型或者具体插件名字，value为对应的工厂对象， 工厂对象生成对应的实例，具体如下图所示：

#### 如何生成对象工厂类呢？
 这里首先不能将这个工作交给插件开发者，一方面开发量增大，另一方面也暴漏系统实现细节；但是也不能框架开发者手工实现，因为框架本身无法预知都有哪些插件需要开发。
 
 ----
 ### 源码
 
 注解：__attribute__(construtor) void register_factory_##clazz##name(); 实现在main()函数调用前进行调用

在主干程序中通过以下的方式调用插件DataHandler:

```c++
DataHandler data_handler = DataHandlerRegister::GetInstanceByName("MyDataHandler");
 
data_handler->Handle(data_list);
```

---

### 实现

```c++
#include <map>
#include <string>
 
class ObjectFactory {
 public:
 ObjectFactory() {}
 virtual ~ObjectFactory() {}
 virtual Any NewInstance() {
 return Any();
 }
 private:
 DISALLOW_COPY_AND_ASSIGN(ObjectFactory);
};
typedef std::map<std::string, ObjectFactory*> FactoryMap;
typedef std::map<std::string, FactoryMap> BaseClassMap;
BaseClassMap& global_factory_map();  // 在.cc文件中实现，保存静态变量factory_map
 
#define REGISTER_REGISTERER(base_class) \
 class base_class ## Registerer { \
 typedef ::registerer::FactoryMap FactoryMap; \
 public: \
 static base_class *GetInstanceByName(const ::std::string &name) { \
 FactoryMap &map = ::registerer::global_factory_map()[#base_class]; \
 FactoryMap::iterator iter = map.find(name); \
 if (iter == map.end()) { \
 LOG(ERROR) << "Get instance " << name << " failed."; \
 return NULL; \
 } \
 return iter->second->NewInstance(); \
 } \
 static bool IsValid(const ::std::string &name) { \
 FactoryMap &map = ::registerer::global_factory_map()[#base_class]; \
 return map.find(name) != map.end(); \
 } \
 }; \
 
#define REGISTER_CLASS(clazz, name) \
 namespace registerer { \
 class ObjectFactory##clazz##name : public ::registerer::ObjectFactory { \
 public: \
 clazz* NewInstance() { \
 return new name(); \
 } \
 }; \
 void register_factory_##clazz##name() { \
 ::registerer::FactoryMap &map = \
 ::registerer::global_factory_map()[#clazz]; \
 if (map.find(#name) == map.end()) \
 map[#name] = new ObjectFactory##clazz##name(); \
 } \
 __attribute__((constructor)) void register_factory_##clazz##name(); \
 ```


