### case 1

```c++
if(condition1){}
if(condition2){}
```

### case 2

```c++
if(condition1){}
else if(condition2){}
```


### case 3
```c++
// guard 1
if(condition1){}

// guard 2
if(condition2){}
```


---

上面有3个例子, 这里要说的是 case1和case2 的情况下, 很容易出现一个问题, 就是你把他们都当做if else 情况.

其实时候, condition条件是不相关的. 比如我推崇的 guard phase写法, 这个时候就要加上空行, 来表示逻辑的block块.
