PhxPaxos是腾讯公司微信后台团队自主研发的一套基于Paxos协议的多机状态拷贝类库。它以库函数的方式嵌入到开发者的代码当中， 使得一些单机状态服务可以扩展到多机器，从而获得强一致性的多副本以及自动容灾的特性。 这个类库在微信服务里面经过一系列的工程验证，并且我们对它进行过大量的恶劣环境下的测试，使其在一致性的保证上更为健壮。

作者：Haochuan Cui, Ming Chen, Junchao Chen 和 Duokai Huang

联系我们：phxteam@tencent.com

想了解更多, 以及更详细的编译手册，请进入中文WIKI，和扫描右侧二维码关注我们的公众号

关于实现的一些原理细节

### link
- https://github.com/Tencent/phxpaxos
