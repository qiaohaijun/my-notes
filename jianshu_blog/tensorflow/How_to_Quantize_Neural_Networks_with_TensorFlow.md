#How to Quantize Neural Networks with TensorFlow

> #如何使用tensorflow 来量化神经网络

When modern neural networks were being developed, the biggest challenge was getting them to work at all! That meant that accuracy and speed during training were the top priorities. Using floating point arithmetic was the easiest way to preserve accuracy, and GPUs were well-equipped to accelerate those calculations, so it's natural that not much attention was paid to other numerical formats.

> 当一个现代的神经网络被开发出来的时候，一个最大的挑战是让它们工作起来！这意味着训练时候的精度和速度是最高优先级。使用浮点运算是保持精度的最简单的方法, GPU 可以很好的加速这些计算, 因此不太关注其他数值格式是很自然的。

These days, we actually have a lot of models being deployed in commercial applications. The computation demands of training grow with the number of researchers, but the cycles needed for inference expand in proportion to users. That means pure inference efficiency has become a burning issue for a lot of teams.

> 现在，我们实际上有很多模型被部署在商业应用中。模型训练的计算需求随着研究人员数量的增加而增加, 但推理所需的计算周期则按照用户的比例扩大。这意味着纯粹推理的效率已经成为许多团队的一个紧迫问题。

That is where quantization comes in. It's an umbrella term that covers a lot of different techniques to store numbers and perform calculations on them in more compact formats than 32-bit floating point. I am going to focus on eight-bit fixed point, for reasons I'll go into more detail on later.

>这就是量子化的用武之地。这是一个总括的术语, 它涵盖了许多不同的技术来存储数字, 并以更紧凑的格式进行计算,而不是32位浮点运算。我将着重于8位的定点数据格式, 原因我稍后会给出更详细的原因。

##Why does Quantization Work?
> 为什么量化能work

Training neural networks is done by applying many tiny nudges to the weights, and these small increments typically need floating point precision to work (though there are research efforts to use quantized representations here too).

>训练神经网络是通过将许多微小的改进加到权重来完成的, 这些小增量通常需要浮点精度来工作 (虽然这个领域也有使用量化表示的研究)。


Taking a pre-trained model and running inference is very different. One of the magical qualities of deep networks is that they tend to cope very well with high levels of noise in their inputs. If you think about recognizing an object in a photo you've just taken, the network has to ignore all the CCD noise, lighting changes, and other non-essential differences between it and the training examples it's seen before, and focus on the important similarities instead. This ability means that they seem to treat low-precision calculations as just another source of noise, and still produce accurate results even with numerical formats that hold less information.

>采用预先训练的模型和运行推理是非常不同的.深层网络的一个神奇特质是,它们往往能很好地处理其输入中的高噪音水平。如果你认为在你刚刚拍摄的照片中认出一个物体,网络就必须忽略所有的CCD噪音、照明变化和它与以前看到的训练示例之间的其他不本质的差异,并聚焦于重要的相似性。这种能力意味着他们似乎把低精度的计算当作是另一种噪音来源, 即使使用较少信息的数值格式,仍然能产生精确的结果。


## Why Quantize?
Neural network models can take up a lot of space on disk, with the original AlexNet being over 200 MB in float format for example. Almost all of that size is taken up with the weights for the neural connections, since there are often many millions of these in a single model. Because they're all slightly different floating point numbers, simple compression formats like zip don't compress them well. They are arranged in large layers though, and within each layer the weights tend to be normally distributed within a certain range, for example -3.0 to 6.0.
The simplest motivation for quantization is to shrink file sizes by storing the min and max for each layer, and then compressing each float value to an eight-bit integer representing the closest real number in a linear set of 256 within the range. For example with the -3.0 to 6.0 range, a 0 byte would represent -3.0, a 255 would stand for 6.0, and 128 would represent about 1.5. I'll go into the exact calculations later, since there's some subtleties, but this means you can get the benefit of a file on disk that's shrunk by 75%, and then convert back to float after loading so that your existing floating-point code can work without any changes.
>神经网络模型可以在磁盘上占用大量的空间,例如,原始的alexnet在浮动格式上超过200MB。几乎所有的大小都用于神经连接的权值,因为一个模型中通常有数百万个。因为它们都是稍微不同的浮点数,简单的压缩格式像zip不能很好地压缩它们。它们排列在大的层次,并且在每一层中,权重通常分布在一定范围内,例如-3.0至6.0。
最简单的量化的动机是通过存储每个层的最小值和最大值来缩小文件大小,然后将每个浮点值压缩为表示在范围内线性范围内的线性组内的最接近实数的8位整数。例如,在- 3.0到6.0范围内, 0字节表示- 3.0 ,一个255表示6.0 ,128表示大约1.5。我稍后将进入精确的计算,因为有一些细微的区别,但这意味着您可以获得在磁盘上缩减75%的文件的好处,然后在加载后转换回浮点数,以便您现有的浮点代码可以不做任何更改。


Another reason to quantize is to reduce the computational resources you need to do the inference calculations, by running them entirely with eight-bit inputs and outputs. This is a lot more difficult since it requires changes everywhere you do calculations, but offers a lot of potential rewards. Fetching eight-bit values only requires 25% of the memory bandwidth of floats, so you'll make much better use of caches and avoid bottlenecking on RAM access. You can also typically use SIMD operations that do many more operations per clock cycle. In some case you'll have a DSP chip available that can accelerate eight-bit calculations too, which can offer a lot of advantages.
Moving calculations over to eight bit will help you run your models faster, and use less power (which is especially important on mobile devices). It also opens the door to a lot of embedded systems that can't run floating point code efficiently, so it can enable a lot of applications in the IoT world.

> 量化的另一个原因是通过完全使用八位输入和输出来减少需要进行推理计算所需的计算资源。这是一个更困难的原因,因为它需要你修改涉及到计算的每个地方, 但是提供了很多潜在的奖励。获取八位值只需要25%的浮点内存带宽,因此您将更好地使用缓存,并避免在ram访问中使用瓶颈效应。您还可以通常使用每个时钟周期执行更多操作的SIMD操作。在某些情况下,你会有一个DSP芯片,可以加速八位计算,这可以提供很多优势。将计算迁移到8位将有助于您更快地运行模型,并使用更少的功耗(这在移动设备上尤为重要)。它还为许多无法高效运行浮点数编码的嵌入式系统打开了大门,使其能够在物联网世界中得到应用。

##Why Not Train in Lower Precision Directly?
There have been some experiments training at lower bit depths, but the results seem to indicate that you need higher than eight bit to handle the back propagation and gradients. That makes implementing the training more complicated, and so starting with inference made sense. We also already have a lot of float models already that we use and know well, so being able to convert them directly is very convenient.

>这里有一些在较低的比特为上进行的实验训练, 但是结果似乎表明你需要高于八位来处理反向传播和反穿梯度。这使得实现训练过程更加复杂, 因此从推理开始使用8bit是有意义的。而且我们已经有很多使用浮点数的模型, 所以能够直接转换它们是非常方便的一件事。

## How Can You Quantize Your Models?
TensorFlow has production-grade support for eight-bit calculations built it. It also has a process for converting many models trained in floating-point over to equivalent graphs using quantized calculations for inference. For example, here's how you can translate the latest GoogLeNet model into a version that uses eight-bit computations:
>tensorflow对于int8的计算具有生产等级支持. 它还有一个过程将许多训练的浮点模型转换为等价的量化之后的int8计算图来进行推理。下面的例子是关于如何将最新的googlenet模型转换为使用int8计算的版本:
```bash
curl http://download.tensorflow.org/models/image/imagenet/inception-2015-12-05.tgz -o /tmp/inceptionv3.tgztar xzf /tmp/inceptionv3.tgz -C /tmp/bazel build tensorflow/tools/quantization/tools:quantize_graphbazel-bin/tensorflow/tools/quantization/tools/quantize_graph \  
--input=/tmp/classify_image_graph_def.pb \  
--output_node_names="softmax" --output=/tmp/quantized_graph.pb \ 
--mode=eightbit
```

This will produce a new model that runs the same operations as the original, but with eight bit calculations internally, and all weights quantized as well. If you look at the file size, you'll see it's about a quarter of the original (23MB versus 91MB). You can still run this model using exactly the same inputs and outputs though, and you should get equivalent results. Here's an example:

>这将产生一个新的模型,运行与原始操作相同的操作,但是在内部使用8位计算,以及所有的权重量化。如果您查看文件大小,您将看到它大约是原始文件的四分之一( 23mb和91mb)。您仍然可以使用完全相同的输入和输出运行这个模型,并且您应该得到相同的结果。以下是一个例子:


```python
# Note: You need to add the dependencies of the quantization operation to the
#       cc_binary in the BUILD file of the label_image program:
##     //tensorflow/contrib/quantization:cc_ops
#     //tensorflow/contrib/quantization/kernels:quantized_opsbazel build tensorflow/examples/label_image:label_imagebazel-bin/tensorflow/examples/label_image/label_image \
--image=<input-image> \
--graph=/tmp/quantized_graph.pb \
--labels=/tmp/imagenet_synset_to_human_label_map.txt \
--input_width=299 \
--input_height=299 \
--input_mean=128 \
--input_std=128 \
--input_layer="Mul:0" \
--output_layer="softmax:0"
```


You'll see that this runs the newly-quantized graph, and outputs a very similar answer to the original.
You can run the same process on your own models saved out as GraphDefs, with the input and output names adapted to those your network requires. I recommend that you run them through the freeze_graph script first, to convert checkpoints into constants stored in the file.

>您会看到它运行新量化的计算图，并输出与原始答案非常相似的结果。
您可以在自己的模型上运行相同的过程，保存为GraphDefs，其输入和输出名称修改为您网络所需的名称。 我建议您先通过freeze_graph脚本运行它们，将检查点转换为存储在文件中的常量。

##How Does the Quantization Process Work?
We've implemented quantization by writing equivalent eight-bit versions of operations that are commonly used during inference. These include convolution, matrix multiplication, activation functions, pooling operations and concatenation. The conversion script first replaces all the individual ops it knows about with quantized equivalents. These are small sub-graphs that have conversion functions before and after to move the data between float and eight-bit. Below is an example of what they look like. First here's the original Relu operation, with float inputs and outputs:
![Relu Diagram](https://www.tensorflow.org/images/quantization0.png)
Then, this is the equivalent converted subgraph, still with float inputs and outputs, but with internal conversions so the calculations are done in eight bit.
![Converted Diagram](https://www.tensorflow.org/images/quantization1.png)
The min and max operations actually look at the values in the input float tensor, and then feeds them into the Dequantize operation that converts the tensor into eight-bits. There's more details on how the quantized representation works later on.
Once the individual operations have been converted, the next stage is to remove unnecessary conversions to and from float. If there are consecutive sequences of operations that all have float equivalents, then there will be a lot of adjacent Dequantize/Quantize ops. This stage spots that pattern, recognizes that they cancel each other out, and removes them, like this:
![Stripping Diagram](https://www.tensorflow.org/images/quantization2.png)
Applied on a large scale to models where all of the operations have quantized equivalents, this gives a graph where all of the tensor calculations are done in eight bit, without having to convert to float.
What Representation is Used for Quantized Tensors?
We approach converting floating-point arrays of numbers into eight-bit representations as a compression problem. We know that the weights and activation tensors in trained neural network models tend to have values that are distributed across comparatively small ranges (for example you might have -15 to +15 for weights, -500 to 1000 for activations on an image model, though the exact numbers will vary). We also know from experiment that neural nets tend to be very robust in the face of noise, and so the noise-like error produced by quantizing down to a small set of values will not hurt the precision of the overall results very much. We also want to pick a representation that's easy to perform calculations on, especially the large matrix multiplications that form the bulk of the work that's needed to run a model.
These led us to pick a representation that has two floats to store the overall minimum and maximum values that are represented by the lowest and highest quantized value. Each entry in the quantized array represents a float value in that range, distributed linearly between the minimum and maximum. For example, if we have minimum = -10.0, and maximum = 30.0f, and an eight-bit array, here's what the quantized values represent:

Quantized | Float--------- | -----0         | -10.0255       | 30.0128       | 10.0

The advantages of this format are that it can represent arbitrary magnitudes of ranges, they don't have to be symmetrical, it can represent signed and unsigned values, and the linear spread makes doing multiplications straightforward. There are alternatives like [Song Han's code books](http://arxiv.org/pdf/1510.00149.pdf) that can use lower bit depths by non-linearly distributing the float values across the representation, but these tend to be more expensive to calculate on.
The advantage of having a strong and clear definition of the quantized format is that it's always possible to convert back and forth from float for operations that aren't quantization-ready, or to inspect the tensors for debugging purposes. One implementation detail in TensorFlow that we're hoping to improve in the future is that the minimum and maximum float values need to be passed as separate tensors to the one holding the quantized values, so graphs can get a bit dense!
The nice thing about the minimum and maximum ranges is that they can often be pre-calculated. Weight parameters are constants known at load time, so their ranges can also be stored as constants. We often know the ranges for inputs (for examples images are usually RGB values in the range 0.0 to 255.0), and many activation functions have known ranges too. This can avoid having to analyze the outputs of an operation to determine the range, which we need to do for math ops like convolution or matrix multiplication which produce 32-bit accumulated results from 8-bit inputs.
What's Next?
We've found that we can get extremely good performance on mobile and embedded devices by using eight-bit arithmetic rather than floating-point. You can see the framework we use to optimize matrix multiplications at [gemmlowp](https://github.com/google/gemmlowp). We still need to apply all the lessons we've learned to the TensorFlow ops to get maximum performance on mobile, but we're actively working on that. Right now, this quantized implementation is a reasonably fast and accurate reference implementation that we're hoping will enable wider support for our eight-bit models on a wider variety of devices. We also hope that this demonstration will encourage the community to explore what's possible with low-precision neural networks.

Except as otherwise noted, the content of this page is licensed under the [Creative Commons Attribution 3.0 License](http://creativecommons.org/licenses/by/3.0/), and code samples are licensed under the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0). For details, see our [Site Policies](https://developers.google.com/terms/site-policies). Java is a registered trademark of Oracle and/or its affiliates.
上次更新日期：三月 8, 2017
