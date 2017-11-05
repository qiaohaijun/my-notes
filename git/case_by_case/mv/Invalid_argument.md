fatal: renaming 'Modern_Industry' failed: Invalid argument

### 解释
1. macos 不区分大小写.

```bash
git mv AAA aaa // will failed
git mv AAA AAA.1
git mv AAA.1 aaa
```
