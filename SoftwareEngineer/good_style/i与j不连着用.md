对于多重循环, 程序员常用的下标变量是ijk


```

for( int i=0; i<x; ++i){
  for(int j=0; j<y; ++j){
    do something
  }
}

```

但是我的建议是, 不要连着用, 因为 i与j太像了. 太容易出错了.

我就在这里踩过雷.


--- 

还有其他的几个组合也不要连着用

- l(char) vs 1(num), 不太容易区分吧
- s(char) vs 5(num) //smith 5mith 一旦字符多了, 就不容易分清楚了
- o(char) vs 0(num)  // 这个得看字体了
