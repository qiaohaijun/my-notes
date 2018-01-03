#### CMAKE_BINARY_DIR
工程的输出目录.

#### CMAKE_CURRENT_BINARY_DIR
当前的 `CMakeLists.txt` 的输出目录, 因为可以包含子目录, 这个就是子工程的输出目录.

#### CMAKE_CURRENT_LIST_FILE
当前的 `CMakeLists.txt` 全路径名称.

#### CMAKE_CURRENT_LIST_DIR
当前的 `CMakeLists.txt` 所在目录.

#### CMAKE_CURRENT_SOURCE_DIR
当前的项目源代码目录.

```cmake
message(${CMAKE_CURRENT_LIST_FILE})
message(${CMAKE_CURRENT_LIST_DIR})
```
