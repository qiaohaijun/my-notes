```
err = foo1();
        if (err != 0)
                goto err1;
        err = foo2();
        if (err != 0)
                goto err2;
.....
err2:
        cleanup2();
err1:
        cleanup1();
...

作者：下愚
链接：https://www.zhihu.com/question/31066849/answer/50519377
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```


这种用法是符合规范的.
