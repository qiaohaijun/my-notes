### 架构图
![](https://github.com/qiaohaijun/mycpt-notes/blob/master/linux/tools/systemd/systemd%E6%9E%B6%E6%9E%84%E5%9B%BE.png)

### systemd Utilities
#### systemctl
#### journalctl
#### notify
#### analyze
#### cgls
#### cgtop
#### loginctl
#### nspawn

----

### System Daemons

#### systemd
#### journald
#### networkd
#### logind
#### user session


----


### systemd targets

#### bootmode
#### shutdown
#### basic
#### reboot

#### multi-user
1. dbus
2. telephony
3. dlog
4. logind

#### graphical
1. user-session

#### user-session
1. display service
2. tizen service


### systemd core
#### manager
#### systemd

#### unit
1. service
2. timer
3. mount
4. target
5. snapshot
6. path
7. socket
8. swap

#### login
1. multiseat
2. inhibit
3. session
4. pam


#### namespace
#### log
#### cgroup
#### dbus

### systemd libraries

1. dbus-1
2. libpam
3. libcap
4. libcryptsetup
5. tcpwrapper
6. libaudit
7. libnotify


### linux kernel
1. cgroups
2. autofs
3. kdbus
