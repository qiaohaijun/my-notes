### epoll接口

epoll操作需要三个接口

```
#include <sys/epoll.h>

int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event* event);
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout);

```

### epoll_create
```
int epoll_create(int size);
```

创建一个epoll的句柄，size用来告诉内核这个监听的数目一共有多大。
这个参数不同于select()中的第一个参数，给出最大监听的fd+1的值。
需要注意的是，当创建好epoll句柄后，它就是会占用一个fd值，
在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，所以在使用完epoll后，必须调用close()关闭，否则可能导致fd被耗尽。


### epoll_ctl
```
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```
epoll的事件注册函数，它不同与select()是在监听事件时告诉内核要监听什么类型的事件epoll的事件注册函数，
它不同与select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。
1. 第一个参数是epoll_create()的返回值，
2. 第二个参数表示动作，用三个宏来表示：
3. 第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事，struct epoll_event结构如下：


- EPOLL_CTL_ADD：注册新的fd到epfd中；
- EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
- EPOLL_CTL_DEL：从epfd中删除一个fd；

```
struct epoll_event {
  __uint32_t events;  /* Epoll events */
  epoll_data_t data;  /* User data variable */
};
```
events可以是以下几个宏的集合：

1. EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
2. EPOLLOUT：表示对应的文件描述符可以写；
3. EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
4. EPOLLERR：表示对应的文件描述符发生错误；
5. EPOLLHUP：表示对应的文件描述符被挂断；
6. EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
7. EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里



### epoll_wait
```
int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
```

等待事件的产生，类似于select()调用。
参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，
这个maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。
该函数返回需要处理的事件数目，如返回0表示已超时。

