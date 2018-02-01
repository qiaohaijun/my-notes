### cmake 自带的模块

find_package(FOO_PACKAGE_NAME REQUIRED)

#### REQUIRED 关键字

如果package是可选的, 可以忽略关键字, 如果不可以忽略

#### 使用命令行查看 cmake自带的模块

```bash
cmake --help-module-list
```
输入 cmake --help 双击tab会有提示.


#### 直接查看
或者直接查看模块路径. 比如Ubuntu linux上, 
模块的路径是 
ls /usr/share/cmake/Modules/:

### 自动定义变量

```bash
$cmake --help-module FindBZip2

cmake version 2.8.12.2
  FindBZip2
       Try to find BZip2

       Once done this will define

         BZIP2_FOUND - system has BZip2
         BZIP2_INCLUDE_DIR - the BZip2 include directory
         BZIP2_LIBRARIES - Link these to use BZip2
         BZIP2_NEED_PREFIX - this is set if the functions are prefixed with BZ2_
         BZIP2_VERSION_STRING - the version of BZip2 found (since CMake 2.8.8)



       Defined in: /usr/share/cmake/Modules/FindBZip2.cmake
```

#### 使用方法

```cmake
cmake_minimum_required(VERSION 2.8)
project(helloworld)
add_executable(helloworld hello.c)
find_package (BZip2)
if (BZIP2_FOUND)
  include_directories(${BZIP_INCLUDE_DIRS})
  target_link_libraries (helloworld ${BZIP2_LIBRARIES})
endif (BZIP2_FOUND)
```

### link
- http://www.voidcn.com/article/p-ydfqrabf-ru.html
