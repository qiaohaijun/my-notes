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
BaseClassMap& global_factory_map();  // 在.cc文件中实现，保存静态变量factory_map
 
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
 }
