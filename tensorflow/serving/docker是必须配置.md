项目开始的时候, `docker`是选配, 但是随着部署的环境发生变化, 我明白如果这个时候还用`docker`, 我就是给自己挖坑.

### GPU版本代码开发环境和部署环境不一致
原来的gpu代码只依赖 cuda, 但是serving代码基于tensorflow. 我想说的是随着tensorflow的版本更迭.
我们依赖的第三方软件越来越多了
1. cuda
2. cudnn
3. nccl
4. tensorrt

据我所知, 以上的所列的软件每个都有三四个选项. 组合爆炸起来就是一个

docker 就像一个jvm一样, 代码写一次, 在所有的环境中部署.


