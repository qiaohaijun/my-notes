### clang-format 是什么
1. 基于clang的命令行工具
2. 可以自动化 C/C++/Obj-C
3. 支持多种风格, Google, Chromium, LLVM, Mozilla, WebKit
4. 支持自定义风格(编写.clang-format文件)

### clang-format 用法

```
// 以LLVM代码风格格式化main.cpp, 结果输出到stdout
clang-format main.cpp -style=LLVM
// 以LLVM代码风格格式化main.cpp, 结果直接写到main.cpp
clang-format -i main.cpp -style=LLVM
// 当然也支持对指定行格式化，格式化main.cpp的第1，2行
clang-format -lines=1:2 main.cpp
```

### link
- http://hokein.me/2016/01/30/clang-format/
