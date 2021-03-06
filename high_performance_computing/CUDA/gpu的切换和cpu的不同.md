### cpu 的线程上下文切换
1. `cpu`上下文切换的代价非常昂贵, 因为每一次上下文切换都要将寄存器里的数据都要保存到 `RAM` 里.
2. 等到重新执行这个任务的时候, 又从 `RAM` 恢复.

### gpu 的线程上下文切换
`GPU` 的体系架构和 `cpu` 很大不同. GPU 同样用到了上下文切换这个概念, 但是它y拥有多个寄存器组而不是单个寄存器组.
因此, gpu 的上下文切换其实就是设置一个寄存器.

因此, 一次上下文切换就只需要进行一次寄存器组调度. 因此和 cpu 相比, gpu 是完全不同的架构. 
gpu 的寄存器切换的效率是 cpu 的几个数量级. 

### cpu 的调度策略
cpu 的调度策略是基于时间分片, 将时间平均分配给每个线程. 一旦线程的数量增加, 上下文的切换的时间百分比就会增加, 那么效率就会急剧下降.

