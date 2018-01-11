1. `.` 当前目录
2. `..` 上级目录

项目内头文件应该按照项目源代码目录树结构排序, 避免使用 UNIX 快捷目录.

这个中情况, 我在mxnet的项目中见到过, 确实让人感觉不专业的感觉.

```c++
# google-awesome-project/src/base/logging.h
#include "base/logging.h" // good
#include "../logging.h" // bad
```
