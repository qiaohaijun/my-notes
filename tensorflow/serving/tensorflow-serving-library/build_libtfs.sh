#! /usr/bin/env bash

# 编译 Tensorflow serving
bazel build -c opt //tensorflow_serving/model_servers:tensorflow_model_server



# 把不需要的对象文件删除掉
# 1. main
# 2. curl, grpc, cloud, hadoop等不需要的模块
# 3. 编译环境中已经有的模块(SSL, protobuf, snappy), 可以剔除掉
#
# ar 是用选项`q`来添加对象文件, 因为会有重名的对象文件.

find -L bazel-out/k8-opt/ -name '*.o' | grep -v '/main\.o$\|\.grpc\.pb\.o$\|/curl/\|/grpc/\|/cloud/\|/hadoop/' | xargs -i ar qv libtensorflow_serving.a '{}'

