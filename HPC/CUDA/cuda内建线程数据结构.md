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

** address = blockIdx.x * blockDim.x + threadIdx.x **




