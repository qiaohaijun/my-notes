### Locations

#### CMAKE_BINARY_DIR
if you are building in-source, this is the same as `CMAKE_SOURCE_DIR`, otherwise this is the top level directory of your build tree


#### CMAKE_COMMAND
this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake). 
Note that if you have custom commands that invoke cmake -E, it is very important to use CMAKE_COMMAND as the CMake executable, 
because CMake might not be on the system PATH.


#### CMAKE_CURRENT_BINARY_DIR 
if you are building in-source, this is the same as `CMAKE_CURRENT_SOURCE_DIR`, otherwise this is the directory where the compiled or generated files from the current CMakeLists.txt will go to.

#### CMAKE_CURRENT_SOURCE_DIR 
this is the directory where the currently processed CMakeLists.txt is located in


### link
- https://cmake.org/Wiki/CMake_Useful_Variables
