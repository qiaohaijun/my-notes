### 任务需求
为调度器做选主操作, 避免脑裂.

调度器是全局性质的, 一主多备份.
但是不能同事多个 master active.

---

### 选型
- floyd
- phxpaxos
- ectd
- qconf
- zookeeper

### floyd

360的开源的raft 协议的库. 可以作为备选.

### phxpaxos
这个是腾讯去年开源的 paxos 类库, 可以说是业界唯一一个开源的 paxos工业级代码.

样例代码里的 phxelect 正好满足需求

### qconf
这个就扯远了, 本来觉得还可以, 但是仔细的看看代码, 是基于 zk 的分布式配置管理系统, 和携程的阿波罗很像. 如果做基于c++的微服务, 可以用.

但是不符合我的需求.

### zookeeper 
zookeepr 历史悠久, 有客户端可以用, 但是需要运维一个 zookeeper 集群, s 公司内部没有单独的这样的 zk 集群业务, 所以会增加项目的复杂度.


### ectd
除了运维业务的复杂度, 还有一个原因就是 ectd 没有找到一个很好的c++ api.

---

### note
现在的获选是 phxpaxos 和 floyd.
