### nagle算法的伪代码.

```
#如果有数据需要发送
1. if there is new data to send 
2.        #分节小于窗口，并且要发发送的数据比一个分节大
3.      if the window size >= MSS and available data is >= MSS  
4.                  #立刻发送整个分节
5.                 send complete MSS segment now                       
6.      else
7.                    #如果信道里有未确认的数据                                                            
8.                if there is unconfirmed data still in the pipe
9.                           #暂缓发送，把数据丢进缓冲区排队，直到收到一个回复，          
10.                        enqueue data in the buffer until an acknowledge is received 
11.                 else
12                            #如果没有未收到的ack，立刻发出去。
13.                         send data immediately             
14.                 end if
15.       end if
16. end if
```
