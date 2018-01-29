### Weight & Activation Precision Calibration

Significantly improves inference performance of models trained in FP32 full precision by quantizing them to INT8, 
while minimizing accuracy loss.

非常显著地推断性能提升. 训练的时候使用FP32, 推断时, 使用量化到INT8.

训练时使用 FP32 全精度模型，推理时可以量化到 INT8，并保持准确率没有明显下降；




### Layer & Tensor Fusion

Improves GPU utilization and optimizes memory storage and bandwidth by combining successive nodes into a single node, 
for single kernel execution

外加 kernel Fusion

将多个连续节点合并为一个节点，减少 Kernel 启动消耗时间，提高 GPU 占用率，降低对内存带宽需求；




### Kernel Auto-Tuning

Optimizes execution time by choosing the best data layer and best parallel algorithms for the target Jetson, Tesla,
or DrivePX GPU platform

自动的选择最优的结果.

从一组 Kernel 中选择最快的算法（如针对不同卷积参数，选择 Winograd/FFT/GEMM 中最快的一种卷积算法）；



### Dynamic Tensor Memory

Reduces memory footprint and improves memory re-use by allocating memory for each tensor only for the duration of its usage.

减少内存占用，张量内存复用；


### Multi-Stream Execution



Scales to multiple input streams, by processing them in parallel using the same model and weights

使用相同模型和权值，并行处理多个输入流；





