### operator new 的三种形式

#### throwing 
```c++
void* operator new (std::size_t size) throw (std::bad_alloc);
```
如果失败, 抛出异常

#### nothrow

```c++
void* operator new(std::size_t size, const std::nothrow_t& nothrow_value);
```

#### placement 


```c++
void* operator new(std::size_t size, void *ptr) throw();
```

```c++

#define __PLACEMENT_NEW_INLINE  
inline void *__cdecl operator new(size_t, void *_P)  
        {return (_P); }  
#if     _MSC_VER >= 1200  
inline void __cdecl operator delete(void *, void *)  
    {return; }  
#endif  
#endif

```

### TODO
未完待续

### link
- http://blog.jobbole.com/106923/


