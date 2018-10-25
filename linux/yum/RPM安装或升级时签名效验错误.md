### 查看是否安装GPG keys
```bash
# rpm -qa gpg*
```

### 查看安装GPG keys 详细信息
```
# rpm -q gpg-pubkey --qf '%{name}-%{version}-%{release} --> %{summary}\n'
```

---

### 解决方法
1. 导入 gpg keys
2. 修改yum源文件, 跳过gpgcheck
3. 安装正确的签名

```
# cd /etc/pki/rpm-gpg
# wget http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-6 
# rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6
```
