前一段时间做项目,因为上线团队没有及时获得`gpu`的机器的审批 所以只能硬着头皮用`cpu`来跑服务. 

现在的机器的体系架构是 `NUMA`, 术语是`非一致内存访问`.
因为非一致性, 所以内存访问也是有了远近亲疏的区别.
1. local memory, local access.
2. remote memory, remote access.

---

### blas 眼中的 CPU

----

### 我的问题
1. 为什么要提出`NUMA`这么个架构?
