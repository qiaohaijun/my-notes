上下文信息.

### PipeContext应该管理, 和维护整个系统的pipe信息
```cpp
std::map<string, PipeInterface*> pipe_infos_;
```

### 各个阶段的超时信息
