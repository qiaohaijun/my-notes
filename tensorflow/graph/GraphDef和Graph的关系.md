1. GraphDef 是序列化的graph, 是可以save和restore的文件.
2. graph 是一个动态的, 可以执行的DAG.


---
### GraphDef
GraphDef类是protobuf中定义的graph结构, 可以将graph结构序列化和反序列化处理,
1. 模型保存
2. 模型加载
3. 分布式数据传输


### Graph
Graph是core/graph模块定义的graph结构, 完成graph相关的操作
1. 构建 construction
2. 剪枝 pruning
3. 划分 partitioning
4. 优化 optimize
5. 运行 execute

Graph和GraphDef可以互相转换
1. Graph::ToGraphDef
2. ConvertGraphDefToGraph



```python
import tensorflow as tf
from tensorflow.python.platform import gfile

with tf.Session() as sess:
    model_filename ='PATH_TO_PB.pb'
    with gfile.FastGFile(model_filename, 'rb') as f:
        graph_def = tf.GraphDef()
        graph_def.ParseFromString(f.read())
        g_in = tf.import_graph_def(graph_def)

LOGDIR='/logs/tests/1/'
train_writer = tf.summary.FileWriter(LOGDIR)
train_writer.add_graph(sess.graph)

```

上面的例子可以很好的说明这个事实.

