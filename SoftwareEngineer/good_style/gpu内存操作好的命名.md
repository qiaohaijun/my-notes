```cxx
#ifndef GPU_UTIL_GPU_MEMORY_H_
#define GPU_UTIL_GPU_MEMORY_H_

#include "task/thread_context.h"
#include "data_nodes/tensor.h"

void* gpu_malloc(size_t malloc_size);
void* host_malloc(size_t malloc_size);

// 0 on success, -1 on error
int memcpy_host_to_device(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_same_device(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_device_to_host(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_host(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_host_to_device_async(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_same_device_async(void* dst, const void* src, size_t count);

// 0 on success, -1 on error
int memcpy_device_to_host_async(void* dst, const void* src, size_t count);

int memset_device(void* dst, int value, int size);

int memset_device_async(void* dst, int value, int size);

int gpu_svector_shuffle(float** dst_ptrs, float**src_ptrs, int single_size, int batch_cnt);

int gpu_svector_shuffle_add_bias(float** dst_ptrs, float**src_ptrs, int single_size, int batch_cnt,
		float* b);


```

好的代码, 读起来就很舒服.


```cxx
int memset_device_async(void* dst, int value, int size,
		dl_kernel::ThreadContext* context) {
	cudaError_t error_id = cudaSuccess;
	error_id = cudaMemsetAsync(dst, value, size, context->thread_default_stream);
	if (error_id != cudaSuccess) {
		_ERROR_RETURN(-1, "cudaMemsetAsync failed, size=%d, %s", size, cudaGetErrorString(error_id));
	}
	return 0;
}

```
