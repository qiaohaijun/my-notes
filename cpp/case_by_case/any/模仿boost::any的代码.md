```c++
#include <iostream>  
#include <list>  
#include <cassert>  
  
//自定义的any类  
class any  
{  
public:  
      
    //保存真正数据的接口类  
    class placeholder  
    {  
    public:       
        virtual ~placeholder()  
        {  
        }  
    public:   
  
        virtual const std::type_info & type() const = 0;  
        virtual placeholder * clone() const = 0;      
    };  
  
    //真正保存和获取数据的类。  
    template<typename ValueType>  
    class holder : public placeholder  
    {  
    public:           
        holder(const ValueType & value): held(value)  
        {  
        }  
  
    public:   
  
        virtual const std::type_info & type() const  
        {  
            return typeid(ValueType);  
        }  
  
        virtual placeholder * clone() const  
        {  
            return new holder(held);//使用了原型模式  
        }  
  
    public:   
  
        //真正的数据，就保存在这里  
        ValueType held;  
    };  
  
public:  
  
    any(): content(NULL)     
    {         
    }  
  
    //模板构造函数，参数可以是任意类型，真正的数据保存在content中  
    template<typename ValueType>  
    any(const ValueType & value): content(new holder<ValueType>(value))  
    {  
    }    
  
    //拷贝构造函数  
    any(const any & other)  
        : content(other.content ? other.content->clone() : 0)  
    {  
    }  
  
    //析构函数，删除保存数据的content对象  
    ~any()  
    {  
        if(NULL != content)  
            delete content;  
    }  
  
private:  
    //一个placeholde对象指针，指向其子类folder的一个实现  
    // 即content( new holder<ValueType>(value) )语句  
    placeholder* content;  
  
    template<typename ValueType> friend ValueType any_cast(const any& operand);  
public:   
  
    //查询真实数据的类型。  
    const std::type_info & type() const  
    {  
        return content ? content->type() : typeid(void);  
    }  
};  
  
  
//获取content->helder数据的方法。用来获取真正的数据  
template<typename ValueType>  
ValueType any_cast(const any& operand)  
{  
    assert( operand.type() == typeid(ValueType) );  
    return static_cast<any::holder<ValueType> *>(operand.content)->held;  
}  
  
//下代码是使用示例  
  
typedef std::list<any> list_any;  
  
void fill_list(list_any& la)  
{      
    la.push_back(10);//存放常数；调用了any的模板构造函数，下同  
    la.push_back( std::string("我是string") );//存放字符串对象；注意la.push_back(“dyunze”)错误，因为会被当错字符串数组  
  
    char* p = "我是常量区字符串abc";  
    la.push_back(p);//可以存放指针，但要注意指针的失效问题  
}  
  
//根据类型进行显示  
void show_list(list_any& la)  
{  
    list_any::iterator it;  
  
    for( it = la.begin(); it != la.end(); it++ )  
    {     
  
        if( (*it).type() == typeid(int) )  
            std::cout<<any_cast<int>(*it)<<std::endl;  
        else if( (*it).type() == typeid(std::string) )  
            std::cout<<any_cast<std::string>(*it).c_str()<<std::endl;  
        else if( (*it).type() == typeid(char*) )  
            std::cout<<any_cast<char*>(*it)<<std::endl;  
    }  
}  
  
int main()  
{  
    list_any la;  
    fill_list(la);  
    show_list(la);  
  
    return 0;  
}  
```
