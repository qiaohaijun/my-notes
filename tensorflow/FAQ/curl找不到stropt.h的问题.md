```
                                         ^
ERROR: /search/odin/system/root/cache/bazel/_bazel_root/683fff147f03ea48cad363efa9ca7db9/external/curl/BUILD:28:1: C++ compilation of rule '@curl//:curl' failed (Exit 1).
external/curl/lib/if2ip.c:47:23: fatal error: stropts.h: No such file or directory
 #  include <stropts.h>
```

### env
- centos 7
- cuda 8
- cudnn 7

tensorflow发布的系统主要支持的是ubuntu.

### 解决思路
- 源码编译curl
- `touch /usr/include/stropts.h`

### link
- https://github.com/tensorflow/serving/issues/320
