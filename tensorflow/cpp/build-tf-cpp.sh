#! /usr/bin/env bash

for i in $(find tensorflow/{c,cc,core} -name "*.h"); do
    mkdir -p ${dest}/${i%/*}
    cp ${i} ${dest}/${i}
done

for i in $(find bazel-genfiles/tensorflow/{cc,core} -name "*.h"); do
    j=${i#bazel-genfiles/}
    mkdir -p ${dest}/${j%/*}
    cp ${i} ${dest}/${j}
done

bazel build //third_party/eigen3:install_eigen_headers
cp -r bazel-genfiles/third_party/eigen3/include/* ${dest}
