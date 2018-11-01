1. 根据 `feed` 和 `fetch` 
2. 反向遍历 graph, 寻找最小依赖的子图
3. 根据执行节点的设备情况, 分裂子图， 这样的图称为 PartitionGraph.
