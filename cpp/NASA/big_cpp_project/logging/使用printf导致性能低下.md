### 背景介绍

背景很简单, 就是为了多输出一些debug 信息, 结果可能真的事太多了, 3000多条信息.

导致cost从10ms耗时, 增加到50ms耗时.

### 教训
logging还是需要专业的logging库, printf只能是凑活用着. 不能当做logging库来用.
