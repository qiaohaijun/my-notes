fatal: renaming 'Modern_Industry' failed: Invalid argument

### 解释
macos 不区分大小写. 所以会出现问题.

### 解决方法
```bash
git mv AAA aaa // will failed
git mv AAA AAA.1
git mv AAA.1 aaa
```
