pthread 锁接口
```cxx
pthread_mutex_t m_mutex;
pthread_mutex_lock( & m_mutex);
pthread_mutex_unlock( & m_mutex);
pthread_mutex_destory( & m_mutex);
```

---
pthread 条件接口

```cxx
pthread_cond_t _cond;
pthread_cond_signal(&_cond);
pthread_cond_timedwait(...);
pthread_cond_broadcast(&m_mutex);
```
