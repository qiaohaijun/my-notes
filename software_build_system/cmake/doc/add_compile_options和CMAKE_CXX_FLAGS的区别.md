cmake 脚本中, 设置编译器选项的方式：
1. add_compile_options
2. set(CMAKE_CXX_FLAGS, "")
3. set(CMAKE_C_FLAGS, "")

### 区别
#### add_compile_options
是在所有的编译器上都生效

#### CMAKE_ABC_FLAGS
1. CMAKE_CXX_FLAGS 针对的是 c++
2. CMAKE_C_FLAGS 针对的是 c


#### add_compile_options的例子
```
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")   
endif(CMAKE_COMPILER_IS_GNUCXX)
```


#### CMAKE_CXX_FLAGS的例子
```
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")   
endif(CMAKE_COMPILER_IS_GNUCXX)
```

---

### link
- https://cmake.org/ 
- https://cmake.org/cmake/help/v3.1/command/add_compile_options.html 
- https://cmake.org/cmake/help/v3.1/command/add_definitions.html 
- https://cmake.org/cmake/help/v3.1/command/set.html 
- https://cmake.org/cmake/help/v3.1/variable/CMAKE_LANG_FLAGS.html
- http://blog.csdn.net/10km/article/details/51731959
