```c++
#ifndef TENSORFLOW_COMPILER_XLA_STATUSOR_H_
#define TENSORFLOW_COMPILER_XLA_STATUSOR_H_

#include "tensorflow/compiler/xla/status.h"
#include "tensorflow/stream_executor/lib/statusor.h"

namespace xla {

// Use steam_executor's StatusOr so we don't duplicate code.
template <typename T>
using StatusOr = ::stream_executor::port::StatusOr<T>;

}  // namespace xla

#endif  // TENSORFLOW_COMPILER_XLA_STATUSOR_H_
```

不止一次看到过这种封装技巧.
