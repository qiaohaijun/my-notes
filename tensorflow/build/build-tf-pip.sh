#! /usr/bin/env bash

pushd tensorflow-1.4.1; \
bazel build \
 -c opt  \
 --copt=-mavx \
 --copt=-msse4.2 \
 --copt=-msse4.1 \
 --copt=-mavx2 \
 --copt=-mfma \
 --verbose_failures  \
 //tensorflow/tools/pip_package:build_pip_package ;\
popd

