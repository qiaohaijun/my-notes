### 模板参数中typename与class的区别

```cxx
template<typenameT> class Widget;
template<class T> class Widget
```

自从`typename`关键字提出来之后, 就有一个问题出现了

**模板参数前的`typename`和`class`的区别**

答案是没有区别. 
- 有人觉的`class`方便就用class
- 有人觉得`typename`语义更加正确就用`typename`


### link
- http://harttle.com/2015/09/09/effective-cpp-42.html
