## 系统要求
### python 3.4

在centos7上需要使用
```
yum install -y rh-python34-python-pip
```

安装**devpi**
```
pip3.4 install -U devpi
pip3.4 install -U devpi-server
pip3.4 install -U devpi-client
pip3.4 install -U devpi-web
```
---

## 系统组成

### 基本架构
1. devpi-server
2. devpi-client
3. devpi-web


## 系统命令
### devpi-server
- devpi-server --start
- devpi-server --stop
- devpi-server --log
- devpi-server --status

**devpi-server --start**



---

## issue
1. 启动devpi-server会使用ipv6
2. /etc/hosts中localhost的配置


