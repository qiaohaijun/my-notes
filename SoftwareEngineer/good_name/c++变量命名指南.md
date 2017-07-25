### 变量命名

1. 变量包括，函数参数，数据成员，单词之间用下划线连接

---

1. 类的成员变量以下划线结尾
2. 结构体不用

---
* a_local_variable
* a_struct_data_member
* a_class_data_member_

---
**举例**

### 普通变量命名
```c++
string table_name; // good  使用下划线
string tablename;  // good  全小写
string tableName;  // bad   混合大小写

```
---

### 类数据成员

不管是静态的还是非静态的，类数据成员都可以很普通变量一样，但是，要接下划线

```c++
class TableInfo {
  ...
   private:
    string table_name_;   // good
    string tablename_;    // good
    static Pool<TableInfo>* pool_; //good
};
```

### 结构体变量
不管使静态的，还是非静态的变量，结构体数据成员都可以和普通变量一样，不用像类那样接下划线：

```c++
struct UrlTableProperties {
  string name;
  int num_entries;
  static Pool<UrlTableProperties> * pool;
};
```
---



---

### 常量命名

声明为 constexpr或者 const的变量，或者在程序运行期间，其值始终保持不变的，命名的时候"k"(小写k)开头，大小写混合.例如：

```c++
const int kDaysInAWeek = 7;
```

---
