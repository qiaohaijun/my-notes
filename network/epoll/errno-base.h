头文件 /usr/include/asm-generic/errno-base.h 的源码


```c
#ifndef _ASM_GENERIC_ERRNO_BASE_H
#define _ASM_GENERIC_ERRNO_BASE_H

#define EPERM 1 /* Operation not permitted */
#define ENOENT2 /* No such file or directory */
#define ESRCH 3 /* No such process */
#define EINTR 4 /* Interrupted system call */
#define EIO 5 /* I/O error */
#define ENXIO 6 /* No such device or address */
#define E2BIG 7 /* Argument list too long */
#define ENOEXEC8 /* Exec format error */
#define EBADF 9 /* Bad file number */
#define ECHILD10 /* No child processes */
#define EAGAIN11 /* Try again */
#define ENOMEM12 /* Out of memory */
#define EACCES13 /* Permission denied */
#define EFAULT14 /* Bad address */
#define ENOTBLK15 /* Block device required */
#define EBUSY 16 /* Device or resource busy */
#define EEXIST17 /* File exists */
#define EXDEV 18 /* Cross-device link */
#define ENODEV19 /* No such device */
#define ENOTDIR20 /* Not a directory */
#define EISDIR21 /* Is a directory */
#define EINVAL22 /* Invalid argument */
#define ENFILE23 /* File table overflow */
#define EMFILE24 /* Too many open files */
#define ENOTTY25 /* Not a typewriter */
#define ETXTBSY26 /* Text file busy */
#define EFBIG 27 /* File too large */
#define ENOSPC28 /* No space left on device */
#define ESPIPE29 /* Illegal seek */
#define EROFS 30 /* Read-only file system */
#define EMLINK31 /* Too many links */
#define EPIPE 32 /* Broken pipe */
#define EDOM 33 /* Math argument out of domain of func */
#define ERANGE34 /* Math result not representable */

#endif
```
