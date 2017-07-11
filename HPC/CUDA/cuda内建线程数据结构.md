### blockIdx

### blockDim

### threadIdx

---

1. Grids map to GPUs
2. Blocks map to the MultiProcessors (MP)
3. Threads map to Stream Processors (SP)
4. Warps are groups of (32) threads that execute simultaneously

---
### blockIdx
blockIdx 是二维的

1. blockIdx.x
2. blockIdx.y

### threadIdx
threadIdx 是三维的
1. threadIdx.x
2. threadIdx.y
3. threadIdx.z

具体的显存地址.

**address = blockIdx.x * blockDim.x + threadIdx.x**

blockdim: number of threads in a block

---

CUDA 并行程序设计 GPU 编程指南

 P78, 第五章 线程网络,线程块以及线程
 
> cuda内建的thread相关的数据结构
 
> - gridDim.x 线程网格X维度上线程块的数量
> - gridDim.y 线程网格Y维度上线程块的数量
> - blockDim.x 一个线程块X维度上的线程数量
> - blockDim.y 一个线程块Y维度上的线程数量
> - threadIdx.x 线程块X维度上的线程索引
> - threadIdx.y 线程块Y维度上的线程索引
 
 ---
 
这个是每个硬件线程的身份证
1. 在哪个block
2. 在block中的索引位置
 
可以根据这些坐标来计算在虚拟的线程grid中,需要计算的数据的位置
1. idx = blockIdx.x * blockDim.x + threadIdx.x
2. idy = blockIdx.y * blockDim.y + threadIdx.y
 
如果是二维数组, 那么直接
- A[idx][idy]就可以访问数据.

如果是一维数组
就需要通过数组的维度信息来计算这个绝对的下标地址了.
 
 ---

