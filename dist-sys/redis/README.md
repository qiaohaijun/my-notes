我没有想到redis的用途这么广.

1. cache
2. redis-cluster

---

### cache
这个作用和memcached是一样的

### redis-cluster
有了cluster保证的可靠性, 那么这个就可以做为一个临时性的内存database来用,为了可靠性,还是要定时落地.
