拿tensorlfow里的一段代码举个例子

```
# from https://github.com/tensorflow/tensorflow/blob/master/tensorflow/python/ops/data_flow_grad.py
ops.NotDifferentiable("Queue")
ops.NotDifferentiable("QueueEnqueue")
ops.NotDifferentiable("QueueEnqueueMany")
ops.NotDifferentiable("QueueDequeue")
ops.NotDifferentiable("QueueDequeueMany")
ops.NotDifferentiable("QueueDequeueUpTo")
ops.NotDifferentiable("QueueClose")
ops.NotDifferentiable("QueueSize")

ops.NotDifferentiable("Stack")
ops.NotDifferentiable("StackPush")
ops.NotDifferentiable("StackPop")
ops.NotDifferentiable("StackClose")

ops.NotDifferentiable("GetSessionHandle")
ops.NotDifferentiable("GetSessionHandleV2")
ops.NotDifferentiable("GetSessionTensor")
ops.NotDifferentiable("DeleteSessionTensor")

```
这里有16个api, 如果随机的顺序, 你需要在大脑里考虑16个事情, 虽然你也知道这里有很多相似性.

如果把相似的放到一起呢, 神器的效果就出来了, 这个api产生了层级效应, 或者说是模块化, 大的模块只有三个. 
当你需要考虑每个模块细节的时候, 你在仔细的进入更加深入的一层.

所以我建议以后写代码的时候, 花点时间对代码顺序调整一下.
