Crash ConsistencyCrash Consistency 的意思是，存储系统可以在故障发生后，保证系统数据的正确性以及数据，元数据的一致性。可以说 Crash Consistency 是存储领域永恒不变的话题。早些年大家热衷于通过各种方法在已实现的文件系统中寻找 Bug，而这两年构造一个新的 Bug Free 的文件系统成为热门的方向。在这方面最早做出突破的是 MIT 的团队的 FSCQ。FSCQ 通过 Coq 作为辅助的形式化验证工具，在 Crash Hoare Logic 的基础上，实现了一个被证明过 Crash Safty 的文件系统。

作者：smartx
链接：https://zhuanlan.zhihu.com/p/34455548
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
