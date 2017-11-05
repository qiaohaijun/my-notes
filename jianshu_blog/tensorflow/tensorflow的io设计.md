几个关键的内容

1. TFRecord (没有找到proto的定义文件)
2.  RecordReader
3.  RecordWriter

这个是一个通用的IO 读写框架, 但是这个框架解决的问题是读写不同类型的数据格式
1. 支持图像
2. 文本
3. 音频
4. 奇怪的格式


因为这个TFRecord中到底存的是什么内容, 只有reader和writer是清楚的. 框架不知道也不需要知道中间是什么格式. 框架只需要知道你实现了read和write的接口就够了.

所以TF使用一套统一的框架, 来读取不同的格式.

这个框架很类似hdfs的数据的record的读写过程.

TODO

---
