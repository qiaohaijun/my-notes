### heron-way

规规矩矩, 将第三方依赖放到`third_party`目录下.
每个subdir中间包含:
1. xyz.tar.gz
2. BUILD
3. xyz.patch


这个方法值得借鉴. 可以保障自己的standalone


### 20190102
今天参考小米的 mace 架构, 发现这个项目也是采用这种方式. 
借鉴成熟的的代码, 算是书法的临摹阶段吧, 有了这些基本的套路之后, 我们可以就自由的发挥自己的主观能动性了.
