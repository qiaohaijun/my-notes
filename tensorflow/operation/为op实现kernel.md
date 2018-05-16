定义好之后interface.

可以为 op 实现多个kernel.


创建 `OpKernel`的子类, 然后overrides `Compute` 函数.

主意OpKernelContext, 从中可以获得input和output的信息.

```c++
#include "tensorflow/core/framework/op_kernel.h"

using namespace tensorflow;

class ZeroOutOp : public OpKernel {
 public:
  explicit ZeroOutOp(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override {
    // Grab the input tensor
    const Tensor& input_tensor = context->input(0);
    auto input = input_tensor.flat<int32>();

    // Create an output tensor
    Tensor* output_tensor = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(),
                                                     &output_tensor));
    auto output_flat = output_tensor->flat<int32>();

    // Set all but the first element of the output tensor to 0.
    const int N = input.size();
    for (int i = 1; i < N; i++) {
      output_flat(i) = 0;
    }

    // Preserve the first input value if possible.
    if (N > 0) output_flat(0) = input(0);
  }
};
```


```
const Tensor& input_tensor = context->input(0);
auto output_flat = output_tensor->flat<int32>();
```

这段代码是获取输入和输出.

`OP_REQUIRES_OK` 这个是assert类似的宏变量.


