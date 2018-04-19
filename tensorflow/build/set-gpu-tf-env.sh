#! /usr/bin/env	bash


## File System
export TF_NEED_S3=0
export TF_NEED_GCP=0
export TF_NEED_HDFS=0

## compute

### cuda 
export TF_NEED_CUDA=1
export TF_CUDA_VERSION=8.0
export CUDA_TOOLKIT_PATH="/usr/local/cuda"
export TF_CUDA_COMPUTE_CAPABILITIES="3.5,5.2,6.1"

### cudnn
export TF_CUDNN_VERSION=6.0.21
export CUDNN_INSTALL_PATH="/usr/local/cudnn-6.0.21"

### opencl
export TF_NEED_OPENCL=0
export TF_NEED_OPENCL_SYCL=0

## MPI
export TF_NEED_MPI=0
export TF_NEED_VERBS=0
export TF_NEED_GDR=0 

## clang
export TF_CUDA_CLANG=0

## blas
export TF_NEED_MKL=0

## other

export TF_NEED_JEMALLOC=1
export TF_ENABLE_XLA=0
export GCC_HOST_COMPILER_PATH="/usr/bin/gcc"
export PYTHON_BIN_PATH="/usr/bin/python"
export CC_OPT_FLAGS="-march=native"
export PYTHON_LIB_PATH="/usr/lib/python2.7/site-packages/"
