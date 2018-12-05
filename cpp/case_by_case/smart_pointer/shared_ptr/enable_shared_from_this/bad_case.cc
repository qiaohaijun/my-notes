#include <iostream>
#include <boost/shared_ptr.hpp>
class Test
{
public:
    //析构函数
    ~Test() { std::cout << "Test Destructor." << std::endl; }
    //获取指向当前对象的指针
    boost::shared_ptr<Test> GetObject()
    {
        boost::shared_ptr<Test> pTest(this);
        return pTest;
    }
};
int main(int argc, char *argv[])
{
    {
        boost::shared_ptr<Test> p( new Test( ));
        boost::shared_ptr<Test> q = p->GetObject();
    }
    return 0;
}
