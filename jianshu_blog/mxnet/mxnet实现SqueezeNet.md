sqeezenet 是一种参数压缩的方式, 模型小了很多, 但是计算没有减少太多.
paper: http://arxiv.org/abs/1602.07360
github: https://github.com/DeepScale/SqueezeNet

mxnet python 模型代码
```python

"""
paper: http://arxiv.org/abs/1602.07360
github: https://github.com/DeepScale/SqueezeNet

@article{SqueezeNet,
    Author = {Forrest N. Iandola and Matthew W. Moskewicz and Khalid Ashraf and Song Han and William J. Dally and Kurt Keutzer},
    Title = {SqueezeNet: AlexNet-level accuracy with 50x fewer parameters and <1MB model size},
    Journal = {arXiv:1602.07360},
    Year = {2016}
}

squeezenet
"""

import find_mxnet
import mxnet as mx

# Basic Conv + BN + ReLU factory
def FireModelFactory(data, size):
    if size == 1:
        n_s1x1 = 16
        n_e1x1 = 64
        n_e3x3 = 64
    elif size == 2:
        n_s1x1 = 32
        n_e1x1 = 128
        n_e3x3 = 128
    elif size == 3:
        n_s1x1 = 48
        n_e1x1 = 192
        n_e3x3 = 192
    elif size == 4:
        n_s1x1 = 64
        n_e1x1 = 256
        n_e3x3 = 256

    squeeze1x1 = mx.symbol.Convolution(
            data   = data, 
            kernel = (1,1), 
            pad    = (0,0),
            num_filter = n_s1x1 )

    relu_squeeze1x1 = mx.symbol.Activation( data=squeeze1x1, act_type="relu" )

    expand1x1 = mx.symbol.Convolution(
            data   = relu_squeeze1x1,
            kernel = (1,1),
            pad    = (0,0),
            num_filter = n_e1x1 )

    relu_expand1x1 = mx.symbol.Activation(data=expand1x1, act_type="relu" )

    expand3x3 = mx.symbol.Convolution(
            data   = relu_squeeze1x1,
            kernel = (3,3),
            pad    = (1,1),
            num_filter = n_e3x3 )

    relu_expand3x3 = mx.symbol.Activation(data=expand3x3, act_type="relu" )
    
    concat = mx.symbol.Concat( *[relu_expand1x1, relu_expand3x3] )

    return concat 

def get_symbol(num_classes = 1000):
    data = mx.symbol.Variable(name="data")

    conv1 = mx.symbol.Convolution(data=data, kernel=(7,7), stride=(2,2), num_filter=96)
    relu_conv1 = mx.symbol.Activation(data=conv1, act_type="relu")
    maxpool1 = mx.symbol.Pooling(data=relu_conv1, kernel=(3,3), stride=(2,2), pool_type="max")

    fire2 = FireModelFactory(data=maxpool1, size=1)
    fire3 = FireModelFactory(data=fire2, size=1)
    fire4 = FireModelFactory(data=fire3, size=2)

    maxpool4 = mx.symbol.Pooling(data=fire4, kernel=(3,3), stride=(2,2), pool_type="max")

    fire5 = FireModelFactory(data=maxpool4, size=2)
    fire6 = FireModelFactory(data=fire5, size=3)
    fire7 = FireModelFactory(data=fire6, size=3)
    fire8 = FireModelFactory(data=fire7, size=4)

    maxpool8 = mx.symbol.Pooling(data=fire8, kernel=(3,3), stride=(2,2), pool_type="max")

    fire9 = FireModelFactory(data=maxpool8, size=4)
    dropout_fire9 = mx.symbol.Dropout(data=fire9, p=0.5)

    conv10 = mx.symbol.Convolution(data=dropout_fire9, kernel=(1,1), pad=(1,1), num_filter=1000)
    relu_conv10 = mx.symbol.Activation(data=conv10, act_type="relu")
    avgpool10 = mx.symbol.Pooling(data=relu_conv10, global_pool="true", kernel=(13,13), stride=(1,1), pool_type="avg")

    flatten = mx.symbol.Flatten(data=avgpool10, name='flatten')

    softmax = mx.symbol.SoftmaxOutput(data=flatten, name="softmax")
    return softmax


```

---

论文中参数的具体表示:
这个表给出的信息很全面, 可以用来对自己的网络结果做比较, 来检查是否网络实现有问题.

![fire_net2.png](http://upload-images.jianshu.io/upload_images/22371-b75c4170e00ae843.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

---
下面是 squeezenet 的网络架构的图示

![squeezenet-227.png](http://upload-images.jianshu.io/upload_images/22371-6f3094288963d222.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


这个图有点太大了, 有谁知道如何resize 这个图的方式, 可以留言给我, 我修改一下.

---

需要注意的地方

** mxnet 的global pooling 的用法**

```python
avgpool10 = mx.symbol.Pooling(data=relu_conv10, global_pool="true", kernel=(13,13), stride=(1,1), pool_type="avg")

```

这个有一个参数 `global_pool`, 这个参数是一个开关, 决定是否是global pooling 操作, 还是普通的pooling操作.
这里还有一个小坑, 应该是代码中间有点小瑕疵, 瑕不掩瑜, 如果有时间了, 我提一个pr.

---

训练脚本

```bash
python train_imagenet.py \
  --batch-size  512 \
  --lr 0.04 \
  --lr-factor .94  \
  --gpus 0,1,2,3 \
  --num-epoch 1000 \
  --network squeezenet \
  --model-prefix model/squeezenet \
  --data-dir /search/data/1k/ \
  --train-dataset train_1k_256.rec \
  --val-dataset val_1k_256.rec \
  --data-shape 227 \
  --log-dir /search/data/user/cptn3m0/logs/ \
  --log-file suqeezenet-1m.log
```

squeezenet 的训练现在已经收敛, 同时对比caffe最新版本, mxnet的收敛速度有明显的优势.

训练结果, 后面给出哈.


caffe 的版本的网络描述文件 prototxt, 以及模型参数caffemodel 可以在下面的网址找到

https://github.com/DeepScale/SqueezeNet

mxnet 版本的squeezenet 我还在训练, 没有找到合适的超参数, 头疼啊!

---
训练结果(还在继续训练中)
```python
TOP1
Epoch[0] Validation-accuracy=0.022162
Epoch[1] Validation-accuracy=0.077706
Epoch[2] Validation-accuracy=0.159512
Epoch[3] Validation-accuracy=0.214047
Epoch[4] Validation-accuracy=0.254604
Epoch[5] Validation-accuracy=0.286223
Epoch[6] Validation-accuracy=0.322604
Epoch[7] Validation-accuracy=0.340362
Epoch[8] Validation-accuracy=0.353355
Epoch[9] Validation-accuracy=0.377770
Epoch[10] Validation-accuracy=0.383929
Epoch[11] Validation-accuracy=0.395719
Epoch[12] Validation-accuracy=0.407187
Epoch[13] Validation-accuracy=0.422513
Epoch[14] Validation-accuracy=0.411445
Epoch[15] Validation-accuracy=0.429787
Epoch[16] Validation-accuracy=0.440171
Epoch[17] Validation-accuracy=0.448293
Epoch[18] Validation-accuracy=0.450375
Epoch[19] Validation-accuracy=0.463289
Epoch[20] Validation-accuracy=0.460333
Epoch[21] Validation-accuracy=0.467395
Epoch[22] Validation-accuracy=0.468770
Epoch[23] Validation-accuracy=0.473502

```

```python
Top5
Epoch[0] Validation-top_k_accuracy_5=0.078205
Epoch[1] Validation-top_k_accuracy_5=0.207151
Epoch[2] Validation-top_k_accuracy_5=0.354402
Epoch[3] Validation-top_k_accuracy_5=0.433394
Epoch[4] Validation-top_k_accuracy_5=0.484714
Epoch[5] Validation-top_k_accuracy_5=0.524042
Epoch[6] Validation-top_k_accuracy_5=0.568060
Epoch[7] Validation-top_k_accuracy_5=0.586814
Epoch[8] Validation-top_k_accuracy_5=0.602932
Epoch[9] Validation-top_k_accuracy_5=0.627730
Epoch[10] Validation-top_k_accuracy_5=0.636201
Epoch[11] Validation-top_k_accuracy_5=0.644149
Epoch[12] Validation-top_k_accuracy_5=0.656270
Epoch[13] Validation-top_k_accuracy_5=0.666474
Epoch[14] Validation-top_k_accuracy_5=0.660881
Epoch[15] Validation-top_k_accuracy_5=0.679548
Epoch[16] Validation-top_k_accuracy_5=0.691067
Epoch[17] Validation-top_k_accuracy_5=0.695876
Epoch[18] Validation-top_k_accuracy_5=0.699000
Epoch[19] Validation-top_k_accuracy_5=0.710499
Epoch[20] Validation-top_k_accuracy_5=0.709810
Epoch[21] Validation-top_k_accuracy_5=0.711854
Epoch[22] Validation-top_k_accuracy_5=0.714525
Epoch[23] Validation-top_k_accuracy_5=0.718730
```
