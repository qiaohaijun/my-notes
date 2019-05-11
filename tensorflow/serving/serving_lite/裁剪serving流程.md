围绕`TensorflowPredictor`来裁剪现有的 `serving` 代码.

### 基础列表
- net_http
- json_tensor
- ...

---

经过裁剪之后的效果
静态链接库的大小从`980M`到`8MB`.

---

`TensorflowPredictor` 最有效的好处是, 有 `BatchSession`

BatchSession 的应用场景.

1. 小模型预测过程的 `gpu` 利用率
2. 开箱即用功能
