```cxx
typedef struct vec_with_prob {
    float prob;
    float vec[100];
} vec_with_prob_t ;
```

这段代码等价于
```cxx
float[101]
```


`不过这段代码的内存友好性差一点.`
