### heron-way

规规矩矩, 将第三方依赖放到`third_party`目录下.
每个subdir中间包含:
1. xyz.tar.gz
2. BUILD
3. xyz.patch


这个方法值得借鉴. 可以保障自己的standalone


### 20190102
今天参考 mace的架构, 发现这个项目也是采用这种方式.
