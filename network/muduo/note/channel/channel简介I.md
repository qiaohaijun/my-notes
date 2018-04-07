### Channel
Channel是Reactor结构中的“事件”，它自始至终都属于一个EventLoop，负责一个文件描述符的IO事件，它包含又文件描述符fd_，但实际上它不拥有fd_，不用负责将其关闭。在Channel类中保存这IO事件的类型以及对应的回调函数，当IO事件发生时，最终会调用到Channel类中的回调函数。Channel类一般不单独使用，它常常包含在其他类中（Acceptor、Connector、EventLoop、TimerQueue、TcpConnection）使用。

### ref
- https://blog.csdn.net/kangroger/article/details/47284957
