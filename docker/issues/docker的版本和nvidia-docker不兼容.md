直接安装nvidia-docker会遇到如下问题:

```
--> Running transaction check
---> Package libnvidia-container1.x86_64 0:1.0.1-1 will be installed
---> Package nvidia-docker2.noarch 0:2.0.3-1.docker18.09.3.ce will be installed
--> Processing Dependency: docker-ce = 3:18.09.3 for package: nvidia-docker2-2.0.3-1.docker18.09.3.ce.noarch
--> Finished Dependency Resolution
Error: Package: nvidia-docker2-2.0.3-1.docker18.09.3.ce.noarch (nvidia-docker)
           Requires: docker-ce = 3:18.09.3
           Available: docker-ce-17.05.0.ce-1.el7.centos.x86_64 (sogou-7-op)
               docker-ce = 17.05.0.ce-1.el7.centos
           Available: docker-ce-18.06.1.ce-3.el7.x86_64 (sogou-7-op)
               docker-ce = 18.06.1.ce-3.el7
 You could try using --skip-broken to work around the problem
 You could try running: rpm -Va --nofiles --nodigest

```

原因是因为默认安装的docker不是nvidia-docker需要的版本.

---

### 解决方案

**查看所有的docker-ce版本**
```
yum list docker-ce --showduplicates | sort -r
```

**结果如下**
```
# yum list docker-ce --showduplicates | sort -r                                                                                                                       1 ↵
Repository epel is listed more than once in the configuration
Repository epel-source is listed more than once in the configuration
Loading mirror speeds from cached hostfile
Loaded plugins: fastestmirror, langpacks
docker-ce.x86_64            18.06.1.ce-3.el7                    sogou-7-op      
docker-ce.x86_64            17.05.0.ce-1.el7.centos             sogou-centos7-op
docker-ce.x86_64            17.05.0.ce-1.el7.centos             sogou-7-op      
Available Packages
```

解决的方案非常简单, 就是直接使用`FullName`
```
yum install -y docker-ce-18.06.1.ce-3.el7.x86_64
```
