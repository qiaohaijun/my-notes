现在想明白了为什么 [tensorflow](www.tensorflow.org) 官网上面放着一个 永不停息的 gif 图示了.

此图我放到下面了.

![tensors_flowing.gif](http://upload-images.jianshu.io/upload_images/22371-7db9c9d9bac4ed35.gif?imageMogr2/auto-orient/strip)

因为一图胜千言. 这个图能说明tf 的运行原理. 以及大家都在讨论的第二代深度学习平台到底是如何运作的.

首先我们来分析一下这个图有哪些大点的模块, 擒贼先擒王嘛!

1.  input
2. Reshape
3. Relu Layer
4. logit Layer
5. softmax
6. cross entropy
7. Gradients
8. SGD Trainer

---

这个网络很简单, 是一个简单的回归模型, 没有拿 cnn 来做例子, 因为 cnn 模型还是有些复杂, 其中的conv 层的表示就会占用很大的一块地方.

## Layer
 
**Relu Layer**

**Logit Layer**

记得去年google刚开源 tf 的时候, 是没有提供conv layer 等等在caffe中作为基本单元的算子, 后来才加上的. 那个时候可真是彻彻底底的 Tensor Flow 啊.


## 计算过程
 
我们可以认为颜色加深是一个使用变量的过程, 那么从图中, 我们可以看到如下过程.
1. 首先从 input 开始, 一层一层的进行 Forward 计算, 
2. 当算到最后的cross entroy的时候, 开始计算梯度, 需要注意一个细节, 那就是计算梯度的时候, 我们是需要权重w和bias 的
3. 然后开始从上往下计算每一个参数的变量, 然后依次更新

---

总结一下

1. 如何用tensor来组织layer
2. 计算梯度的流程
3. 更新的流程

---
