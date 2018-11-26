可读性.
表达具体的语义.

什么类型的class是noncopybale

### 独一无二的数据结构
1. queue
2. stack

---

### noncopyable让我免于犯错
使用了`noncopyable`作为tag给class打了对象, 帮助我在不小心对具有对象语义的class执行拷贝操作的时候, 在编译阶段就狠狠的提醒了我, 免于在runtime的时候费事查找诡异问题.
