#ifndef CLICKQUERY_SERVICE_LOG_HPP
#define CLICKQUERY_SERVICE_LOG_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "Platform/log.h"

SS_LOG_MODULE_USE(web_qa_short_server);

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION <= 30400
//#pragma GCC system_header
//#warning use high version gcc
#endif

#ifdef DEBUG
#define CODE_INFO               __FILE__, __PRETTY_FUNCTION__, __LINE__
#define CODE_INFO_FORMAT        "[%s:%s:%u] "
#else
#define CODE_INFO               ""
#define CODE_INFO_FORMAT        "%s"
#endif

#ifdef NEED_DEBUG
#define _DEBUG_2(fmt, ...)\
({\
    time_t __time_buf__;\
    tm __localtime_buf__;\
    char __strftime_buf__[sizeof("19820429 23:59:59")];\
    time(&__time_buf__);\
    localtime_r(&__time_buf__, &__localtime_buf__);\
    strftime(__strftime_buf__, sizeof("19820429 23:59:59"), "%Y%m%d %H:%M:%S", &__localtime_buf__);\
    fprintf(stderr, "[_DEBUG_2]  [%s] [%08lX] " CODE_INFO_FORMAT fmt "\n",\
            __strftime_buf__, pthread_self(), CODE_INFO, ##__VA_ARGS__);\
})
#else
#define _DEBUG_2(fmt, ...)
#endif

#ifdef NEED_DEBUG_ONCE
#define _DEBUG_3(fmt, ...)\
({\
    time_t __time_buf__;\
    tm __localtime_buf__;\
    char __strftime_buf__[sizeof("19820429 23:59:59")];\
    time(&__time_buf__);\
    localtime_r(&__time_buf__, &__localtime_buf__);\
    strftime(__strftime_buf__, sizeof("19820429 23:59:59"), "%Y%m%d %H:%M:%S", &__localtime_buf__);\
    fprintf(stderr, "[_DEBUG_2]  [%s] [%08lX] " CODE_INFO_FORMAT fmt "\n",\
            __strftime_buf__, pthread_self(), CODE_INFO, ##__VA_ARGS__);\
})
#else
#define _DEBUG_3(fmt, ...)
#endif



#define _INFO(fmt, ...)\
({\
    time_t __time_buf__;\
    tm __localtime_buf__;\
    char __strftime_buf__[sizeof("19820429 23:59:59")];\
    time(&__time_buf__);\
    localtime_r(&__time_buf__, &__localtime_buf__);\
    strftime(__strftime_buf__, sizeof("19820429 23:59:59"), "%Y%m%d %H:%M:%S", &__localtime_buf__);\
    fprintf(stderr, "[INFO]  [%s] [%08lX] " CODE_INFO_FORMAT fmt "\n",\
            __strftime_buf__, pthread_self(), CODE_INFO, ##__VA_ARGS__);\
})

#define _ERROR(fmt, ...)\
({\
    time_t __time_buf__;\
    tm __localtime_buf__;\
    char __strftime_buf__[sizeof("19820429 23:59:59")];\
    time(&__time_buf__);\
    localtime_r(&__time_buf__, &__localtime_buf__);\
    strftime(__strftime_buf__, sizeof("19820429 23:59:59"), "%Y%m%d %H:%M:%S", &__localtime_buf__);\
    fprintf(stderr, "[ERROR] [%s] [%08lX] " CODE_INFO_FORMAT fmt "\n",\
            __strftime_buf__, pthread_self(), CODE_INFO, ##__VA_ARGS__);\
})

#define _ERROR_RETURN(ret, fmt, ...)\
({\
    _ERROR(fmt, ##__VA_ARGS__);\
    return ret;\
})

#define _ERROR_EXIT(ret, fmt, ...)\
({\
    _ERROR(fmt, ##__VA_ARGS__);\
    exit(ret);\
})

#define _ERROR_CONTINUE(fmt, ...)\
({\
    _ERROR(fmt, ##__VA_ARGS__);\
    continue;\
})

#define _ERROR_BREAK(fmt, ...)\
({\
    _ERROR(fmt, ##__VA_ARGS__);\
    break;\
})

#define WASTE_TIME_US(past)\
({\
    timeval __now__;\
    gettimeofday(&__now__, NULL);\
    (__now__.tv_sec - past.tv_sec) * 1000000 + (__now__.tv_usec - past.tv_usec);\
})

#define WASTE_TIME_US_INTERVAL(start, end)\
({\
    (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);\
})

#define WASTE_TIME_MS(past)\
({\
    timeval __now__;\
    gettimeofday(&__now__, NULL);\
    (__now__.tv_sec - past.tv_sec) * 1000 + (__now__.tv_usec - past.tv_usec) / 1000;\
})

#define SILENT_STDERR(x)\
({\
    int __err_fd__ = dup(STDERR_FILENO);\
    close(STDERR_FILENO);\
    int __ret__ = (x);\
    dup2(__err_fd__, STDERR_FILENO);\
    close(__err_fd__);\
    __ret__;\
})

#endif /* CLICKQUERY_SERVICE_LOG_HPP */
