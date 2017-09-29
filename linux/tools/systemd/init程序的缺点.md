init是linux历史上的启动进程

#### 启动命令
```bash
$ sudo /etc/init.d/apache2 start
$service apache2 start
```

### init 不足
#### 启动时间长
init 进程是串行启动, 只有前一个启动之后, 后面的才可以继续启动.
#### 启动脚本复杂
init进程只负责启动脚本, 不管其他的事情. 脚本需要自己处理各种情况.
