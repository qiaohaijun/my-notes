> 所谓的Most Vexing Parse是个什么东西呢。它是C++中的一个特性，这个特性表述起来其实是这样子的：
> 凡是长得像是函数声明的，就是函数声明

**凡是长得像是函数声明的，就是函数声明**

#### 不像函数声明的
```c++
string my_str;  
vector<int> my_ivec; 
```


#### 可以解析为函数声明的
```c++
string my_str();  
vector<int> my_ivec();  
```
所以c++中,对于没有参数的class 默认ctor, 你就不能写成带括号的形式. 因为会被解析为函数.

---


```c++
int f(double d)； //声明接受一个double参数d，返回值为int类型的函数  
int f(double (d))；//效果一样，参数名外的括号会被忽略  
int f(double)；//直接省略参数名  
```

```c++
int g(double (*pf)())； //声明接受一个无参数返回类型为double的函数指针pf参数，返回值为int类型的函数  
int g(double pf())；//效果一样，pf是隐式函数指针  
int g(doble ())；//直接省略参数名  
```

---

### 破解之法
1. uniform initialization
2. scott的解法



### note
心得, 有时候你一直搞不明白的道理, 很大的一种可能性, 不是你脑子有问题, 而是你的已有的知识体系.

已有的知识体系和作者的知识体系不是很一致. 导致作者的讲的内容, 很可能你看不明白. 
这种情况其实很好处理, 那就是打开心扉, 不要死磕一个阐述, 而是从多个角度, 来看待.

### link
- http://blog.csdn.net/yamingwu/article/details/48025433
- http://www.zkt.name/c-s-most-vexing-parse/
