 在java中，可以写一个仅接受扩展所选类型的类的泛型类
 ```java
 public class ObservableList<T extends List> {
  ...
 }
 ```
 
 这里使用 extends 关键字可以完成
 
 ----
 
 ### c++ 的tricks
 
 #### 使用 Boost的static_assert
 现在这个static_assert已经是标准库里的一个组件了。
 
 ```cxx
 template<typename T>
 class ObservableList {
 //Yes, the double parentheses are needed, otherwise the comma will be seen as macro argument separator
  BOOST_STATIC_ASSERT((is_base_of<List, T>::value));// 
  ...
   
 }
 ```
 
 ----
 
 未完
 
 
