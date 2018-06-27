最近在做基于transformer模型的离线翻译项目.

优化过程.
1. 使用原版tensorflow-1.8.0
2. 使用mkl优化
3. 修改默认内存分配器. 使用bfc算法


效果


---
### 原生tensorflow
1. bz=4, time=30s
这个速度实在是太慢了, 完全没有实际使用价值.

### mkl
```
KMP_BLOCKTIME=1
KMP_SETTINGS=1
OMP_THREAD_NUM=20
```
1. bz=4, cpu=xx00%, time=16s
2. numactl --cpubind=0 --membind=0 效果最好, time=14s

### bfc算法的威力
1. bz=4, time=12s
2. bz=40, time=44s
3. bz=80, time=54s
4. bz=160, time=90s

就是这个效果.
