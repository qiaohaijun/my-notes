### `#`是将传入的变量字符串化
```c++
#define PRINTCLASS(ClassName) printout(#ClassName)

PRINTCLASS(ClassName);
// printout("ClassName");
```

在宏中传入的是一个类名, 但函数printout需要传入的是一个字符串, 这个时候需要把出啊让你的变量转化为一个字符串.

### `##`在宏中是连接两个单元
有时候定义一个变量, 但是这个变量的名字需要从外面输入, 这个时候需要用`##`

```c++
#define DeclareSomething(ArgumentName,i) int ArgumentName##i
DeclareSomething(rr,4);
//=> int rr4
```
`##` 可以连接两个宏, 也可以连接任意其他的.
```c++
#define DeclareSomething(ArgumentName) int ArgumentName##index
DeclareSomething(rr);
//=> int rrindex;
```
`##`后果面跟着宏的变量

```c++
#define DeclareSomething(ArgumentName) int index##ArgumentName
DeclareSomething(rr);
//=> int indexrr
```



