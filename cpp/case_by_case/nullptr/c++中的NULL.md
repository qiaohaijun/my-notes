```c++
/*Define NULL pointer value*/
#ifndef NULL
  #ifdef __cplusplus
    #define NULL 0
  #else /*__cplusplus*/
    #define NULL ((void*)0)
  #endif /*__cplusplus*/
#endif /*NULL*/

记住一点, 就是C++中的`NULL`就是整数`0`.
