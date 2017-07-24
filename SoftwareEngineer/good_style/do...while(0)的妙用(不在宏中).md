It is a way to simplify error checking and avoid deep nested if's. For example:

```cxx
do {
  // do something
  if (error) {
    break;
  }
  // do something else
  if (error) {
    break;
  }
  // etc..
} while (0);
```

如果不这么写，换种写法，应该这么写：
```cxx
if (error) {
  ...
  return xxx;
}
if (error) {
  ...
  return xxx;
}

if (error) {
  ...
  return xxx;
}

```
这样的代码显然不太友好，在程序中有多个return.

---

```cxx
        do {
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
                if (pthread_attr_setstacksize(&attr, stack_size))
                        break;

                if (thread_num == 0 || (m_thread = (pthread_t*)malloc(thread_num * sizeof(pthread_t))) == NULL)
                        break;

                pthread_barrier_init(&m_barrier, NULL, thread_num + 1);
                for (i=0; i<thread_num; i++)
                        if (pthread_create(m_thread+i, &attr, run_svc, this))
                                break;

                if ((m_thread_num = i) != thread_num)
                        break;

                ret = 0;
        } while (false);
        
```        


https://stackoverflow.com/questions/257418/do-while-0-what-is-it-good-for
