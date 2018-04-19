#! /usr/bin/env bash

#source ./unset-tf-env.sh
source ./set-gpu-tf-env.sh
source ./util.sh

INFO "begin ..."

pushd tensorflow-1.4.1; ./configure; popd; \
cd serving-1.4.0; \
bazel build \
 -c opt  \
 --copt=-mavx \
 --copt=-msse4.2 \
 --config=cuda \
 --crosstool_top=@local_config_cuda//crosstool:toolchain \
 --verbose_failures  \
 //tensorflow_serving/model_servers:libtfs_wrapper.so
 

#--config=monolithic \
