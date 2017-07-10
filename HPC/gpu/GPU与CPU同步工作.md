# synchronzing GPU and CPU

### 所有的kernel的启动都是异步的

### Memcopie都是同步的
1. cudaMemcpyFromDeviceToHost
2. cuda

### cudaThreadSynchronize()


### Asynchronous CUDA calls Provide
1. non-blocking memcopies
2. ability to overlap memcopies and kernel execution
