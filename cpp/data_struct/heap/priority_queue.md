c++ STL
### 模板类型

```
template <class T, class Container = vector<T>,
  class Compare = less<typename Container::value_type> > class priority_queue;
```

1. 默认容器是 vector<T>
2. 默认比较器是 less<T>

### 默认操作
名字就是优先队列, 实现的是大顶堆.

- 标准库默认使用元素类型的<操作符来确定它们之间的优先级关系。



----

```
#include <iostream>  
#include <queue>  
using namespace std;  
struct Node{  
    int x, y;  
}node;  
struct cmp{  
    bool operator()(Node a,Node b){  
        if(a.x==b.x) return a.y>b.y;  
        return a.x>b.x;}  
};  
  
 int main(){  
    priority_queue<Node,vector<Node>,cmp>q;  
    for(int i=0;i<10;i++){  
        node.x=i;  
        node.y=10-i/2;  
        q.push(node);     
    }     
    while(!q.empty()){  
        cout<<q.top().x<<' '<<q.top().y<<endl;  
        q.pop();  
    }  
    return 0;  
}  
```
