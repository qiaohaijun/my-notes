最近在做一个关于transformer项目, 因为需要导出savedmodel从而可以使用tensorflow的serving框架.

基于 t2t v1.013项目, 发现这个项目本身没有使用export_savedmodel的功能. 所以想要尝试将更新的一些版本中类似的功能在旧版本上实现.

在这个项目中发现了.

1. tensorflow.contrib.learn.estimator　和 tensorflow.estimator不是简单的挪动了位置的关系, 是不兼容的
2. t2t 新的版本基于新的 tensorlfow.estimator进行了全新的重构. 


### 重构的好处
1. 代码更加清晰
2. 功能进行了模块化封装

### 重构的坏处
对于懒惰的项目组, 这个就是灾难性的事故.
