看过很多cmake的文件, set命令是定义变量相关的内容.

### 语法
```cmake
set(variable value)
```
 
 
```cmake
# 设置C编译器的位置
set (CMAKE_CXX_COMPILER, "C:\\MinGW\\bin\\g++")
# 启用C99标准
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
# 启用C++ 11标准
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# 启用警告
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
```
