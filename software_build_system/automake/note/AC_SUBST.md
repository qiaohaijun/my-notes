### 语法
```
AC_SUBST(VARIABLE, [VALUE])
```

### 解析

定义变量 `$VARIABLE=VALUE`到makefile中

```
AC_SUBST([FOO],[foo])
```
等价

```
FOO=foo
AC_SUBST([FOO])
```


---

### PS

简而言之, 这个就是定义变量.
