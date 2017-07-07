有人说这里的原因是
1. pass by value
2. pass by ref

---

注意这里和c/c++语言中的的malloc的区别

### malloc函数
```
void * malloc( the memory you need )
```

### cudaMalloc函数
```
 cudaMalloc(&ptr_d_memory, the gpu memory you need)
```
