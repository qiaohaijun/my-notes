CNN Network quantization 阶段总结
====

## 提纲
* Tensorflow quantization &  8bit quantization 简介
* 实验结果
* 8bit 计算的有效性
* NVIDIA GPU P4 and P40 性能



### Tensorflow quantization 简介

#### 开发人员

TF-quantization 原来是 tensorflow 的一个 contrib 中的内容， 现在已经移到 master 分支中的核心代码中。

详细描述这个工作的内容是 `Pete Warden（google brain tensorflow group 中负责 mobile 和 embeding 设备的 team lead）

#### 代码

TF-quantization 项目提供了以下工具和代码
* `graph-quantization` 脚本，用来将32bit 浮点型的参数（weight和conv filter 等等）quantizate 为 8bit 的定点
* 提供了常用的 CNN 网络需要的 ops 的quantization 版本， 这个是它实现的  [operator](https://github.com/tensorflow/tensorflow/tree/r0.11/tensorflow/contrib/quantization/kernels) 的页面,下面是我从中找出的几个 ops

```
1. quantized_conv_ops
2. quantized_pooling_ops
3. quantized_concat_ops
4. ....
```



#### 原理示意图

TF-quantization 主要思想就是将 32bit 的浮点运算通过 ==graph-quantization== 脚本转化为8bit 的 fixedpoint 运算

32bit 浮点运算| 8bit 定点运算
---|---
![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/quantization0.png)|![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/quantization1.png)


----






### 实验

这个实验过程中使用的代码公司内部的服务器 git.sogou-inc.com 上。
1. TF-quantization: http://git.sogou-inc.com/qiaohaijun/TF-quantization
2. TF-inception: http://git.sogou-inc.com/qiaohaijun/TF-Inception
```
补充说明：
TF-quantization 实现了一系列便于实验的脚本， TF-inception 项目是用来对系统做性能评估用的对比脚本。
```

#### 模型

这里使用的模型是 google brain 的发表的 inception-v3 深度 CNN 网络



![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/inception_v3_architecture.png)

#### 实验结果

模型 | Size |	Top1 精度 | Top5 精度 |	速度@CPU|速度@GPU
---|---|---|---|---|---
Origin model |	97MB |	0.7872|0.9436	|==12/sec==|==70/sec==
Quantized Model	| 23MB 	|0.7663	|0.9319 |==1.6/sec==|==N/A==

```
补充说明
1. quantized ops 没有实现 GPU 版本的算子，所以只能使用 CPU
2. origin ops 可以运行在 GPU 设备和 CPU 上， 所以有两个结果
```
**精度**
* 0.0209@TOP1
* 0.0117@TOP5


**性能**
1. 没有采用量化的 TF 模型， GPU 版本是 CPU 版本的 5.8X
2. 量化之后的模型， 性能没有提高，反而下降很多， 未量化的模型是量化之后的模型7.5X

这个结果出乎意料，但是仔细阅读 pete 的blog之后， 发现很多人的结果和我的实验结果是一致的，都是性能有损失，我下面放了一张截图。

![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/pete_quantization_slow.png)

这个结果应该是因为 CPU 中并没有对 int8 计算单元做优化造成的，具体的分析需要有一定的 CPU 架构和性能的相关知识，具体分析暂时无法给出。

#### 结论

原本希望通过这项技术来我们现有的特征抽取和线上深度模型的速度，但是实验结果给出了一个否定的答案。


## 8bit 计算的有效性

我们前面提到过的 Pete Warden 写过一篇文章 **<Why are Eight Bits Enough for Deep Neural Networks?>**, 文章中他提出了一项假设，就是连接拓扑要比连接拓扑中的具体数值更加重要， 没有具体的数学证明， 可以作为一种思维的开阔来看待这篇文章。


前一段时间 google 推出了 GNMT， 基于神经网络的翻译服务，同时发表了[论文](https://arxiv.org/pdf/1609.08144v2.pdf)，下图是该系统的一个网络架构。 
![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/GNMT-arch.png)

论文第六部分
**Quantizable Model and Quantized Inference** 主要内容是GNMT如何使用TPU硬件和quantization来实现 low latency的服务的。为了可以得更好的结果， 仅仅需要在训练过程中增加简单的正则操作。

下图是采用了简单正则的网络 quantized 之后和没有量化的网络进行对比，发现最终的性能只是略微下降。

![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/GNMT_normal_vs_quantized_training.png)


TPU 是今天谷歌公开的一款 ASIC， 研发工作开始于三年前， 通过网上的一些信息， 我们现在大概明确了 TPU 设备的作用。 和开始是大家认为谷歌开发的可以替代 NVIDIA GPU  的高性能芯片不同， TPU 是一个以 INT8，INT16 定点运算单元为主的芯片， 不参与训练任务， 主要执行线上 inference 的工作。

![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/Google-Tensor-Processing-Unit-TPU-three-generations-Moores-Law.jpg)


### P4 以及 P40 GPU 卡

和现在我们使用的K40，M40相比， Pascal系列的 GPU 卡增加了 INT8 单元。

![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/p4_p40_m4_m40.png)


P4 和 P40 中增加大量的 int8 计算单元，这种新的芯片架构对于线上服务来讲是非常有帮助的。 下图是 P4 和 CPU 以及 FPGA 的对比结果。

![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/P4_vs_CPU.png)

尤其是 P4 GPU卡的功耗只有50W

NVIDIA 作为一家提供软件和硬件一体化的公司， 在提供了支持 INT8 计算的GPU的同时， 提供了一个 DL 推断框架 **==TensorRT==**，这个框架的使用和谷歌提供的Tensorflow quantization 非常的相似。 下图就是这个过程的图示。
![image](https://coding.net/u/qiaohaijun/p/my-doc/git/raw/master/data/TRT_Graphics_FINAL.png)

其中的第二个阶段 TensorRT optimizer 应该是 Tensorflow 的 quantization 一样的逻辑过程。


----




## 引用
1. https://github.com/tensorflow/tensorflow/tree/r0.11/tensorflow/contrib/quantization/kernels
2. https://petewarden.com/2016/05/03/how-to-quantize-neural-networks-with-tensorflow/
3. GNMT:Google’s Neural Machine Translation System: Bridging the Gap between Human and Machine Translation
4. [Why are Eight Bits Enough for Deep Neural Networks?](：https://petewarden.com/2015/05/23/why-are-eight-bits-enough-for-deep-neural-networks/)
5. https://developer.nvidia.com/tensorrt
