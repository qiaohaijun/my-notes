### 提纲
- 定义声明分离
- flags集中处理

### 定义声明分离
```bash
control_gflags.h
control_gflags.cc
```

1. `control_gflags.h`是声明
2. `control_gflags.cc`是定义

### flags集中处理
模块需要的gflags, 不要分散的定义在不同的代码里, 集中定义在一个文件里.
1. 可控
2. 清晰
