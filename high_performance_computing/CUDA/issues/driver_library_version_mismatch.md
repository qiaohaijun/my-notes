Driver/library version mismatch
===

这个问题经常在系统更新过了nvidia driver之后出现.

这个问题出现的原因是kernel mod 的 Nvidia driver 的版本没有更新，一般情况下，重启机器就能够解决，如果因为某些原因不能够重启的话，也有办法reload kernel mod。



```
Failed to initialize NVML: Driver/library version mismatch

```

### 问题背景

更新了系统的 nvidia-drirver. 


### 问题解决方法
1. unload nvidia kernel mod
2. reload nvidia kernel mod

这时，就要一点一点的卸载整个驱动了，首先要知道现在kernel mod 的依赖情况，首先我们从错误信息中知道，nvidia_modeset nvidia_uvm 这两个 mod 依赖于 nvidia, 所以要先卸载他们


### REF

- https://comzyh.com/blog/archives/967/
