### Weight & Activation Precision Calibration

Significantly improves inference performance of models trained in FP32 full precision by quantizing them to INT8, 
while minimizing accuracy loss.

非常显著地推断性能提升. 训练的时候使用FP32, 推断时, 使用量化到INT8.




### Layer & Tensor Fusion

Improves GPU utilization and optimizes memory storage and bandwidth by combining successive nodes into a single node, 
for single kernel execution

外加 kernel Fusion

### Kernel Auto-Tuning

Optimizes execution time by choosing the best data layer and best parallel algorithms for the target Jetson, Tesla,
or DrivePX GPU platform

自动的选择最优的结果.

### Dynamic Tensor Memory

Reduces memory footprint and improves memory re-use by allocating memory for each tensor only for the duration of its usage.


### Multi-Stream Execution



Scales to multiple input streams, by processing them in parallel using the same model and weights




