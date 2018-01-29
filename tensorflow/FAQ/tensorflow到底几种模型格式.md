### checkpoint(*.ckpt)

在训练 TensorFlow 模型时，每迭代若干轮需要保存一次权值到磁盘，称为“checkpoint”，如下图所示：

这种格式文件是由 tf.train.Saver() 对象调用 saver.save() 生成的，只包含若干 Variables 对象序列化后的数据，不包含图结构，所以只给 checkpoint 模型不提供代码是无法重新构建计算图的。

载入 checkpoint 时，调用 saver.restore(session, checkpoint_path)。

---

### GraphDef(*.pb)

这种格式文件包含 protobuf 对象序列化后的数据，包含了计算图，可以从中得到所有运算符（operators）的细节，也包含张量（tensors）和 Variables 定义，但不包含 Variable 的值，因此只能从中恢复计算图，但一些训练的权值仍需要从 checkpoint 中恢复。下面代码实现了利用 *.pb 文件构建计算图：

TensorFlow 一些例程中用到 *.pb 文件作为预训练模型，这和上面 GraphDef 格式稍有不同，属于冻结（Frozen）后的 GraphDef 文件，简称 FrozenGraphDef 格式。这种文件格式不包含 Variables 节点。将 GraphDef 中所有 Variable 节点转换为常量（其值从 checkpoint 获取），就变为 FrozenGraphDef 格式。代码可以参考 tensorflow/python/tools/freeze_graph.py

*.pb 为二进制文件，实际上 protobuf 也支持文本格式（*.pbtxt），但包含权值时文本格式会占用大量磁盘空间，一般不用。

---

### SavedModel

在使用 TensorFlow Serving 时，会用到这种格式的模型。该格式为 GraphDef 和 CheckPoint 的结合体，另外还有标记模型输入和输出参数的 SignatureDef。从 SavedModel 中可以提取 GraphDef 和 CheckPoint 对象。

其中 saved_model.pb（或 saved_model.pbtxt）包含使用 MetaGraphDef protobuf 对象定义的计算图；assets 包含附加文件；variables 目录包含 tf.train.Saver() 对象调用 save() API 生成的文件。

更多细节可以参考 tensorflow/python/saved_model/README.md。

