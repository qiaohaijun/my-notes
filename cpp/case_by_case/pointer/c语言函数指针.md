首先要说的是
1. 函数指针的语法确实不好理解，尤其有了std::function，更加突出了函数指针的不人性化

```c
void MyFun(int x);
//指针表示法
void (*FunP)(int);
```

```c
//自行包含头文件
void MyFun(int x);    
void (*FunP)(int );    //申明一个用以指向同样参数，返回值函数的指针变量。

int main(int argc, char* argv[])
{
   MyFun(10);     //这里是调用MyFun(10);函数
   FunP=MyFun;  //将MyFun函数的地址赋给FunP变量
   FunP(20);    //这是通过函数指针变量来调用MyFun函数的。

      return 0;
}

void MyFun(int x)  //这里定义一个MyFun函数
{
   printf(“%d\n”,x);
}
```
