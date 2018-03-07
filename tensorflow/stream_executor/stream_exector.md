### 代码注释
```
// The StreamExecutor is a single-device abstraction for:
//
// * Loading/launching data-parallel-kernels
// * Invoking pre-canned high-performance library routines (like matrix
//   multiply)

```


这个streamExecutor 是一个单设备(单块gpu卡)的抽象, 具体工作
1. loading/lauching 数据并行的kernel
2. 调用提前打包好的高性能的计算库. (cublas)


### 包含的头文件

```c++

#include "tensorflow/stream_executor/device_description.h"  // IWYU pragma: export
#include "tensorflow/stream_executor/device_memory.h"    // IWYU pragma: export
#include "tensorflow/stream_executor/device_options.h"  // IWYU pragma: export
#include "tensorflow/stream_executor/event.h"           // IWYU pragma: export
#include "tensorflow/stream_executor/kernel.h"       // IWYU pragma: export
#include "tensorflow/stream_executor/kernel_spec.h"  // IWYU pragma: export
#include "tensorflow/stream_executor/launch_dim.h"   // IWYU pragma: export
#include "tensorflow/stream_executor/multi_platform_manager.h"  // IWYU pragma: export
#include "tensorflow/stream_executor/platform.h"     // IWYU pragma: export
#include "tensorflow/stream_executor/stream.h"       // IWYU pragma: export
#include "tensorflow/stream_executor/stream_executor_pimpl.h"  // IWYU pragma: export
#include "tensorflow/stream_executor/timer.h"  // IWYU pragma: export
```
