**tensorflow 1.8.0**
```bash
#!/usr/bin/env bash

set -e
set -o pipefail

if [ -z "$PYTHON_BIN_PATH" ]; then
  PYTHON_BIN_PATH=$(which python || which python3 || true)
fi

# Set all env variables
CONFIGURE_DIR=$(dirname "$0")
"$PYTHON_BIN_PATH" "${CONFIGURE_DIR}/configure.py" "$@"    #  这行表明该configure文件是通过调用 对应的configure.py来完成配置过程的

echo "Configuration finished"
```

### 原理分析
`configure.py` 是工作的主要部分, 代码通过 `configure(.sh)` 来配置 `python` 解释器. 然后把工作交给 `configure.py`来做.
1. configure.sh 相当于是代理
2. configure.py 是真正的干活的好同志.



---

### `configure.py` 获取配置信息
```python
  set_build_var(environ_cp, 'TF_NEED_JEMALLOC', 'jemalloc as malloc',
                'with_jemalloc', True)
  set_build_var(environ_cp, 'TF_NEED_GCP', 'Google Cloud Platform',
                'with_gcp_support', True, 'gcp')
  set_build_var(environ_cp, 'TF_NEED_HDFS', 'Hadoop File System',
                'with_hdfs_support', True, 'hdfs')
  set_build_var(environ_cp, 'TF_NEED_AWS', 'Amazon AWS Platform',
                'with_aws_support', True, 'aws')
  set_build_var(environ_cp, 'TF_NEED_KAFKA', 'Apache Kafka Platform',
                'with_kafka_support', True, 'kafka')
  set_build_var(environ_cp, 'TF_ENABLE_XLA', 'XLA JIT', 'with_xla_support',
                False, 'xla')
  set_build_var(environ_cp, 'TF_NEED_GDR', 'GDR', 'with_gdr_support',
                False, 'gdr')
  set_build_var(environ_cp, 'TF_NEED_VERBS', 'VERBS', 'with_verbs_support',
                False, 'verbs')
```

这些是真正收集信息的地方. 
如果对配置很熟悉的话, 可以直接将这些作为环境变量暴露给 `bazel`

---

