```
bazel build -c opt --copt=-msse3 --copt=-msse4.1 --copt=-msse4.2 --copt=-mavx //tensorflow/tools/pip_package:build_pip_package
```

这里可以看到, tensorflow编译的时候需要的cpu指令集.
1. sse4.1
2. sse4.2
3. avx
4. sse3

### 获取cpu指令集信息

cat /proc/cpuinfo

