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
