这个思路很有意思, tensorflow根目录下configure文件是一个bash脚本.

```bash
#!/usr/bin/env bash

set -e
set -o pipefail

if [ -z "$PYTHON_BIN_PATH" ]; then
  PYTHON_BIN_PATH=$(which python || which python3 || true)
fi

# Set all env variables
"$PYTHON_BIN_PATH" configure.py

echo "Configuration finished"
```

#### 过程
1. 加载 `bash`
2. 查找 `python`
3. 调用 `configure.py`
