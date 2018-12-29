将git的项目导入到svn中.

### 从svn中clone代码

```
# git svn int http://ip/svn/demo/trunk  demo
# git svn fetch -r HEAD
```

### 添加 git repo
```
cd demo
git remote add git  http://ip/path/demo.git
```

### 获取 git branch
```
git fetch git master    #获取git仓库的master分支
git fetch git 1.0       #获取git仓库的1.0分支
git fetch git           #获取所有git分支
```

### 此时本地git的分支情况
```
demo git:(master) git branch -a
* master              #默认对应svn
  remotes/git-svn     #svn分支
  remotes/git/1.0     #远程git的1.0分支
  remotes/git/master  #远程git的master分支
```

### 将git代码合并到svn分支
```
git merge  git-master
```

### update and commit
```
git svn rebase
git svn dcommit
```





### link
https://blog.csdn.net/wyongqing/article/details/79053803
