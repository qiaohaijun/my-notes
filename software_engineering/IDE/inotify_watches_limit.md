### 配置文件目录
1. /etc/sysctl.conf
2. /etc/systctl.d


---
### 内容
```
 fs.inotify.max_user_watches = 524288
```

### 执行命令
```
sysctl -p --system
```

### link
- https://confluence.jetbrains.com/display/IDEADEV/Inotify+Watches+Limit
