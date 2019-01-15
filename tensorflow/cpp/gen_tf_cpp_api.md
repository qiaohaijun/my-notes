### 获取代码
git clone --recursive https://github.com/tensorflow/tensorflow

### 编译源码
bazel build //tensorflow:libtensorflow_cc.so 



1. bazel-genfiles,
2. bazel-out,
3. bazel-tensorflow,
4. bazel-testlogs,
5. bazel-bin

### include lib64
```
mkdir /usr/local/include/tf
cp -r bazel-genfiles/ /usr/local/include/tf/
cp -r tensorflow/* /usr/local/include/tf/tensorflow/
cp -r third_party /usr/local/include/tf/
cp -r bazel-bin/tensorflow/*.so /usr/local/lib/
```
### proto
```
cp -r bazel-genfiles/ /usr/local/include/tf/
cp -r tensorflow/* /usr/local/include/tf/tensorflow/
```
