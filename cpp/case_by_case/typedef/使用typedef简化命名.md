```cxx
union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t
#define __have_pthread_attr_t 1
#endif
```

这段代码使用了`typedef`把 `union pthread_attr_t` 简化了一下 `pthread_attr_t`
