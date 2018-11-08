phx系列代码是微信的同学们的作品. 

前一段时间, 网上流传T的技术落后的传言. 因为没有在T工作过, 不置可否. 

简单地看了一下phx的代码, 我觉得有必要写一些东西出来.

### 软件工程质量堪忧
1. build系统老旧
2. 文件命名很随意
3. 稀少的单元测试


---

### build 系统老旧
编译系统使用的是AutoMake, 这里我有偏见, 我觉得automake很落后. 
使用automake简直就是一种折磨.
1. ! 易读
2. ! 易维护
3. ! 易入门

---

### 文件命名很随意

- keepmasterthread.cpp
- keepmasterthread.h

这样的例子比比皆是.  这是哪门子的命名规范. 不客气的说这就是乱码啊.


#### 下划线命名
- keep_master_thread.cpp
- keep_master_thread.h

#### 大写字母命名
- KeepMasterThread.cpp
- KeepMasterThread.h

都要更有信息含量.

---

### 单元测试
几乎没有测试, 单元测试对于现代软件的重要性, 不用多说了, 为啥不重视呢, 小厂子不重视也罢, 你可是大厂啊.

没有单元测试
1. 怎么做到的快速迭代?
2. 敏捷开发的?
