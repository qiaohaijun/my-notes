## 引出问题


在学习CUDA的矩阵运算当中，如果定义了M*N的矩阵A，都会有一个相应的参数ldA，也就是A的leading dimensions，但是一直搞不懂是哪个数，例如3*2维矩阵

```
1 2
3 4
5 6
```

### 问题
1 什么是leading dimensions


---
> This refers to the first index in the dimension
 you specify for the matrix. For example: 
 If you had dimensioned table as table(20,10) 
 then the leading dimension would be 20. 

---


leading dimension 就是主维度.

## 参考
- http://www.netlib.org/utk/forums/netlib/messages/272.html
