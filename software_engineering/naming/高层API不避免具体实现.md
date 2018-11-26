这个周末的时候, 仔细思考的.

#### 原来的名字
```
ProcessPredictRequestByPipeline()
```

#### 好的名字
```
AsyncPrecessPredictRequest()
```

我认为最好的名字就是后一个, 好处有几个
1. `ByPipeline` 是把具体的实现暴露出来给用户
2. `Async` 就是告诉我们的这个处理是异步的, 底层实现是如何, 我就不告诉你.
