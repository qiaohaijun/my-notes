### 简洁

一个带锁的queue.

1. std::queue
2. std::mutex

据说性能不是特别好, 没关系


这个queue是对std::queue的封装

```cpp
QueueWithMutex<PipeTask*>  work_queue;
```


### TODO
将泛型参数改为smart_ptr.
