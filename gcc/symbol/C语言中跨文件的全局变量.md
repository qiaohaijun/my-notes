func.c
```c++
// func.c
int buf = 0;

void func() {
  buf = 2;
  /* Do something else */
}
```

main.c
```c++
// main.c
#include <stdio.h>

int buf;
void func();

int main() {
  buf = 1;
  func();
  printf("%d\n", buf);
  return 0;
}
```

这里`func.c`文件中有`buf`, `main.c`中间也有`buf`.

1. 全局变量buf有两个, 没有extern, 所以是两个.


### TODO
1. run the code

### 符号有强弱
- 函数和初始化的全局符号被标记为strong
- 未初始化的全局符号被标记为weak

### 链接器的解析规则
- 同一个符号不允许有多个strong定义；
- 假如一个符号有一个strong定义和多个weak定义，那么采用该符号的strong定义；
- 假如一个符号有多个weak定义，那么`选取任意`一个weak定义

由于两个变量一个初始化了，一个没有初始化，所以一个是strong，一个是weak，所以连接器在符号解析时会把他们当成一个。


### link
- https://www.byvoid.com/zhs/blog/c-global-variables-in-multiple-files
