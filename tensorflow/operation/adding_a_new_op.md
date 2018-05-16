### There are several reasons why you might want to create a custom C++ op
1. 使用现有的代码组合无法完成自己的需求
2. 使用现有代码的组合无法满足性能要求
3. You want to hand-fuse a composition of primitives that a future compiler would find difficult fusing.

使用 "media pooling" 作为例子.

1. performance-efficient
2. memory-efficient


---

### 创建 custom op的流程
1. 在c++文件中注册新的ops
2. 使用c++实现ops
3. 创建python wrapper这个是**可选择的**
4. 创建一个funciton来计算 gradients
5. 测试ops. 我们一般使用python来做测试,  因为python方便.
### ref
- https://www.tensorflow.org/extend/adding_an_op
