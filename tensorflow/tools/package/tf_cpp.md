### 编译 TF
#### clone源码
```
git clone https://github.com/tensorflow/tensorflow
cd tensorflow
```

#### build 动态链接库
```
bazel build //tensorflow::libtensorflow_cc.so
bazel build //tensorflow::libtensorflow_framework.so
```

### 整理头文件
```
mkdir /usr/local/include/tf/tensorflow

// tf自身的文件
cp -r tensorflow/core /usr/local/include/tf/tensorflow
cp -r tensorflow/cc /usr/local/include/tf/tensorflow
// bazel编译的文件

cp -r bazel-genfiles/ /usr/local/include/tf/
// 3rdparth
cp -r third_party /usr/local/include/tf

```

### 动态链接
```
cp -r bazel-bin/tensorflow/libtensorflow_cc.so /usr/local/lib/
cp -r bazel-bin/tensorflow/libtensorflow_framework.so /usr/local/lib/
```


### link
https://ce39906.github.io/2018/09/10/Tensorflow-%E7%BC%96%E8%AF%91%E5%8F%8A%E5%BA%94%E7%94%A8C-%E5%8A%A8%E6%80%81%E5%BA%93/
