Makefile 是用来自动化的编译和链接的.

makefile的语法非常简单

```make
object: dep1 dep2 deps
  action
```

因为我们在写makefile的时候将目标和依赖进行了关联, 所以对文件做了修改的时候, makefile就可以根据这个依赖关系来做出判断, 哪些object需要重新build.

### 优点
1. 语法非常简单
2. 自动化的build
3. 增量build

### 缺点
1. 对于大型项目,很容易的遗漏依赖
2. 容易出错
3. 修改起来不太容易

> Makefile的 基本结构不是 很复杂,但当一个程序开发人员开始写Makefile时,经常会怀疑自己写的 是 否符合惯例,而且自己写的 Makefile经常和自己的 开发环境相关联,当系统环境变量或路径发生了变化后,Makefile可能还要跟着修改.这样就造成了手工书写Makefile的 诸多问题,automake恰好能很好地帮助我们解决这些问题.


