头文件/usr/include/asm-generic/erno.h源码

```c
#ifndef _ASM_GENERIC_ERRNO_H
#define _ASM_GENERIC_ERRNO_H

#include <asm-generic/errno-base.h>

#define EDEADLK35 /* Resource deadlock would occur */
#define ENAMETOOLONG36 /* File name too long */
#define ENOLCK37 /* No record locks available */
#define ENOSYS38 /* Function not implemented */
#define ENOTEMPTY39 /* Directory not empty */
#define ELOOP 40 /* Too many symbolic links encountered */
#define EWOULDBLOCKEAGAIN /* Operation would block */
#define ENOMSG42 /* No message of desired type */
#define EIDRM 43 /* Identifier removed */
#define ECHRNG44 /* Channel number out of range */
#define EL2NSYNC45 /* Level 2 not synchronized */
#define EL3HLT46 /* Level 3 halted */
#define EL3RST47 /* Level 3 reset */
#define ELNRNG48 /* Link number out of range */
#define EUNATCH49 /* Protocol driver not attached */
#define ENOCSI50 /* No CSI structure available */
#define EL2HLT51 /* Level 2 halted */
#define EBADE 52 /* Invalid exchange */
#define EBADR 53 /* Invalid request descriptor */
#define EXFULL54 /* Exchange full */
#define ENOANO55 /* No anode */
#define EBADRQC56 /* Invalid request code */
#define EBADSLT57 /* Invalid slot */

#define EDEADLOCKEDEADLK

#define EBFONT59 /* Bad font file format */
#define ENOSTR60 /* Device not a stream */
#define ENODATA61 /* No data available */
#define ETIME 62 /* Timer expired */
#define ENOSR 63 /* Out of streams resources */
#define ENONET64 /* Machine is not on the network */
#define ENOPKG65 /* Package not installed */
#define EREMOTE66 /* Object is remote */
#define ENOLINK67 /* Link has been severed */
#define EADV 68 /* Advertise error */
#define ESRMNT69 /* Srmount error */
#define ECOMM 70 /* Communication error on send */
#define EPROTO71 /* Protocol error */
#define EMULTIHOP72 /* Multihop attempted */
#define EDOTDOT73 /* RFS specific error */
#define EBADMSG74 /* Not a data message */
#define EOVERFLOW75 /* Value too large for defined data type */
#define ENOTUNIQ76 /* Name not unique on network */
#define EBADFD77 /* File descriptor in bad state */
#define EREMCHG78 /* Remote address changed */
#define ELIBACC79 /* Can not access a needed shared library */
#define ELIBBAD80 /* Accessing a corrupted shared library */
#define ELIBSCN81 /* .lib section in a.out corrupted */
#define ELIBMAX82 /* Attempting to link in too many shared libraries */
#define ELIBEXEC83 /* Cannot exec a shared library directly */
#define EILSEQ84 /* Illegal byte sequence */
#define ERESTART85 /* Interrupted system call should be restarted */
#define ESTRPIPE86 /* Streams pipe error */
#define EUSERS87 /* Too many users */
#define ENOTSOCK88 /* Socket operation on non-socket */
#define EDESTADDRREQ89 /* Destination address required */
#define EMSGSIZE90 /* Message too long */
#define EPROTOTYPE91 /* Protocol wrong type for socket */
#define ENOPROTOOPT92 /* Protocol not available */
#define EPROTONOSUPPORT93 /* Protocol not supported */
#define ESOCKTNOSUPPORT94 /* Socket type not supported */
#define EOPNOTSUPP95 /* Operation not supported on transport endpoint */
#define EPFNOSUPPORT96 /* Protocol family not supported */
#define EAFNOSUPPORT97 /* Address family not supported by protocol */
#define EADDRINUSE98 /* Address already in use */
#define EADDRNOTAVAIL99 /* Cannot assign requested address */
#define ENETDOWN100 /* Network is down */
#define ENETUNREACH101 /* Network is unreachable */
#define ENETRESET102 /* Network dropped connection because of reset */
#define ECONNABORTED103 /* Software caused connection abort */
#define ECONNRESET104 /* Connection reset by peer */
#define ENOBUFS105 /* No buffer space available */
#define EISCONN106 /* Transport endpoint is already connected */
#define ENOTCONN107 /* Transport endpoint is not connected */
#define ESHUTDOWN108 /* Cannot send after transport endpoint shutdown */
#define ETOOMANYREFS109 /* Too many references: cannot splice */
#define ETIMEDOUT110 /* Connection timed out */
#define ECONNREFUSED111 /* Connection refused */
#define EHOSTDOWN112 /* Host is down */
#define EHOSTUNREACH113 /* No route to host */
#define EALREADY114 /* Operation already in progress */
#define EINPROGRESS115 /* Operation now in progress */
#define ESTALE116 /* Stale NFS file handle */
#define EUCLEAN117 /* Structure needs cleaning */
#define ENOTNAM118 /* Not a XENIX named type file */
#define ENAVAIL119 /* No XENIX semaphores available */
#define EISNAM120 /* Is a named type file */
#define EREMOTEIO121 /* Remote I/O error */
#define EDQUOT122 /* Quota exceeded */

#define ENOMEDIUM123 /* No medium found */
#define EMEDIUMTYPE124 /* Wrong medium type */
#define ECANCELED125 /* Operation Canceled */
#define ENOKEY126 /* Required key not available */
#define EKEYEXPIRED127 /* Key has expired */
#define EKEYREVOKED128 /* Key has been revoked */
#define EKEYREJECTED129 /* Key was rejected by service */

/* for robust mutexes */
#define EOWNERDEAD130 /* Owner died */
#define ENOTRECOVERABLE131 /* State not recoverable */

#define ERFKILL 132/* Operation not possible due to RF-kill */

#endif
```
