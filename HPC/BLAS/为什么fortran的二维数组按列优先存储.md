## 为科学家服务的fortran
- fortran是为科学家服务的.
- 在数学上, 向量默认为列向量
- 所以, 如果从科学家的角度来考虑, 按列优先存储, 天经地义. 以为如果我要读取一个列向量, 直接连续读取就可以, 很方便.

---

`内存中是没有行列的概念的`, 不管是二维数组,还是N维的tensor,在内存中都是一条线.

在这个物理存储的层面上, Fortran和C是没有区别的.

下面表示 [1,2,3,4,5,6,7,8]
![image](https://github.com/qiaohaijun/mycpt-notes/blob/master/img/blas/fortran%E8%A1%8C%E5%88%97%E5%AD%98%E5%82%A8.gif?raw=true)



## 参考
- https://www.zhihu.com/question/21766240
- http://fcode.cn/guide-45-1.html

