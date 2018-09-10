1. GraphDef 是序列化的graph, 是可以save和restore的文件.
2. graph 是一个动态的, 可以执行的DAG.

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

