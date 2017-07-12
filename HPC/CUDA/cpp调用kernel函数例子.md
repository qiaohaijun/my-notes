test.h的代码
```
//
// Created by root on 7/12/17.
//

#ifndef DESM_GPU_TEST_H
#define DESM_GPU_TEST_H

#endif //DESM_GPU_TEST_H
void  hello(char *a,int*b);

```

---


test.cu的代码
```
#include "cuda.h"
#include "test.h"
#include "cuda_runtime.h"
__global__
void KERNEL_hello(char *a, int *b)
{
    a[threadIdx.x] += b[threadIdx.x];


}

void hello(char* a, int *b){
    KERNEL_hello<<<16,1>>>(a,b);

}
```


---

上面代码的写法的好处
1. kernel函数使用KERNEL前缀, 增加可读性
2. cpp的函数的名字和kernel函数的名字一致, 可读性很高
3. 头文件放到.h文件中
4. kernel和cpp代码放到cu文件中

很好的代码布局策略.
