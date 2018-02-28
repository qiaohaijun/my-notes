系统定义目录

/usr/lib/rpm/macros


### 用户自定义

用户家目录下建立一个名为.rpmmacros的隐藏文件(注意前面的点不能少，这是Linux下隐藏文件的常识)

通常情况下.rpmmacros文件里一般只有一行内容，比如:

点击(此处)折叠或打开

```
%_topdir    $HOME/myrpmbuildenv
```


### rpmdev-setuptree

执行 rpmdev-setuptree 会在当前用户家目录下的rpmbuild目录(如果该目录不存在也会被自动创建)里自动建立上述目录。 
