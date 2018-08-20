### Scope 作用域的概念
```
int a = 1;
{
    int b = 1;
    xxxx
    // (1)
}
// (2)
```

(1)和(2)就是不同的作用域,这个是编程语言领域的概念.

ScopeGuard就是利用了这个知识. 代码执行出了作用域之后就会触发动作.

```
{
    defer {
        print("print 2");
    }
    print("print 1");
}

```

输出结果就是.

```
print 1
print 2
```

这段代码很像 golang.

`defer`本质上就是 ScopeGuard. 但是

### ScopeGuard在不同语言中的名字
1. defer @golang
2. defer @swift
3. onExit
4. ON_SCOPE_EXIT

### ScopeGuard的用处
自动释放资源,

```
FILE* file = fopen(filename, "rb");
xxxxx
if (xxx)
{
    xxxxx
}
else
{
    xxxxx
}

fclose(file);
```

#### 这段代码是脆弱的
- fopen 和 fclose 相隔太远，难以看出它们的对应关系。
- 另外中间有任何异常，中途 return，fclose 都不能被执行，就有资源泄露。
- 假如将这段代码复用，搬到另外地方，容易漏掉 fclose。

#### 使用goto trick来避免资源泄露
```
    if (xxxx) {
        goto fail;
    }

    if (xxxx) {
        goto fail;
    }

    xxx 正常操作
    return 1;

fail:
    fclose(file);
    xxxx 释放资源
    return 0;
```


这里引出来一个编程规范, 
```
一个函数只能有一个return, 不能中途return. 
```
其实这里的规范要解决的就是资源泄露的问题.


#### 使用 scopeGuard解决问题
```
FILE* file = fopen(filename, "rb");
defer {
    fclose(file);
};

xxxxx
if (xxx)
{
    xxxxx
}
else
{
    xxxxx
}
```

好处
1. 资源申请和释放一起, 清晰易懂, 安全
2. 如果分配和释放分隔两地就容易出现问题.



```
CGContextSaveGState(context);
defer {
    CGContextRestoreGState(context);
};

drawer.beginDraw(); 
defer {
    drawer.endDraw();
}
```
```
static void test_cpp()
{
    void* p = malloc(1000);
    ON_SCOPE_EXIT
    {
        free(p);
    };
}
```
---

https://zhuanlan.zhihu.com/p/21303431
