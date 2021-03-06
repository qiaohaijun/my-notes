### 从 `sql` 说起
`bazel` 在我看来是一种声明性质的工具, 最接近的一个比喻是 `sql`. 你只需要表达你的意图, 后面的编译系统会将你的意图翻译为代码.
这样就将 `DBA` 和 `sql` 编译系统的开发人员通过`sql`语法进行了解耦.

#### dba 的工作
- 专注于自己的业务的数据处理逻辑
- 只需要了解 sql 语法
- 了解常见的 sql 执行效率
- 专注于业务开发

#### sql 编译系统的开发人员的工作
- 在不同的后端平台上开发 `sql` 的编译系统
- 构建 sql 的 `logic plan`
- 构建 sql 的 `physical plan`

总而言之就是专注于编译系统的开发.

通过两个方面的任务分解, 每个业务方向的开发人员都可以聚集与自己的领域. 不用做到跨领域的知识积累就可以高效的完成自己的领域工作.


---

### `bazel` 的角色分解
1. build-sys 用户
2. build-sys 开发人员

#### build-sys 用户
- 熟悉到精通自己的领域需要的编程语言
- 熟悉自己的代码的依赖关系
- 熟悉 bazel 的用法


#### build-sys 开发人员
- 专注于代码的依赖构建
- 如何构建object
- object 文件的缓存工作
- 这也是一个编译系统相关的工作
- 这是一个系统软件开发工作

这个两个用户的分解工作通过`bazel`语法很好的解决了. 

如果没有这个分解, 毫不夸张的说, 如果稍微复杂一点的工程就会让开发人员将大量的时间浪费在这个项目的构建之中. 为啥我知道呢, 因为这里有血和泪啊.
