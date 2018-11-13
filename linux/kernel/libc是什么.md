### libc
libc 是linux系统调用上的api.

### glibc
`glibc`中的`g`是`gnu`的意思


`glibc`是linux 系统最底层的api, 几乎所有的运行时库都会依赖于glibc.
#### overview
Any Unix-like operating system needs a C library: the library which defines the `system calls` and other basic facilities 
such as open, malloc, printf, exit... 
The GNU C Library is used as the C library in the GNU systems and most systems with the Linux kernel.

#### Project Goals:  

The GNU C Library is primarily designed to be a portable and high performance C library. 
It follows all relevant standards including ISO C11 and POSIX.1-2008. 
It is also internationalized and has one of the most complete internationalization interfaces known.


#### History

The history of Unix and various standards determine much of the interface of the C library. 
In general the GNU C Library supports the ISO C and POSIX standards. 
We also try to support the features of popular Unix variants (including BSD and System V) when those do not conflict with the standards. 
Different compatibility modes (selectable when you compile an application) allow the peaceful coexistence of compatibility support for different varieties of Unix. 

---

libc, glibc在一个层次，都是C的标准实现库，是操作系统级别的基石之一。



### glib
`glib`这个名字非常具有迷惑性, 因为有一个`g`, 会让人认为是`gnu`, 其实这里的glib中的`g`是 `gtk`的意思.
