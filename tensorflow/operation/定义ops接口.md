> You define the interface of an op by registering it with the TensorFlow system.
In the registration, you specify the name of your op, its inputs (types and names) and outputs (types and names), 
as well as docstrings and any attrs the op might require.

您可以通过向TensorFlow系统注册来定义op的接口。 
在注册过程中，您可以指定您的操作的名称，其输入（类型和名称）和输出（类型和名称），
以及文档字符串和操作可能需要的任何attrs。

---
> To see how this works, suppose you'd like to create an op that takes a tensor of int32s and outputs a copy of the tensor, with all but the first element set to zero. 
To do this, create a file named zero_out.cc. Then add a call to the REGISTER_OP macro that defines the interface for your op:

为了看看它是如何工作的，假设你想创建一个运算符，该运算符需要一个int32s张量并输出张量的一个副本，除了第一个元素之外的所有元素都设置为零。 为此，创建一个名为zero_out.cc的文件。 然后向REGISTER_OP宏添加一个调用，以定义op的接口：



```c++
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"

using namespace tensorflow;

REGISTER_OP("ZeroOut")
    .Input("to_zero: int32")
    .Output("zeroed: int32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
      c->set_output(0, c->input(0));
      return Status::OK();
    });
    
```    

注册 ops, 需要
1. Input
2. Output
3. SetShapeFn
