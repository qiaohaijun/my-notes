### cudnn
cudnn的命名比较简单, 因为 cudnn 只是依赖cuda
- cudnn-9.0-7.2.1
- cudnn-9-0-7.2.1
我觉得还是选择第一种命名方式, 这样可以认为9.0是一个group

### nccl
nccl和cudnn一样, 只依赖一个cuda

### tensorrt
这个依赖cudnn和cuda
所以我们命名的时候就有点麻烦了, 比如说
- cuda 9.0
- cudnn 7.2.1

**tensorrt-9.0-7.2-2.2.3**
通过使用`.`和`-`将各种信息默认编码进入了命名中.
