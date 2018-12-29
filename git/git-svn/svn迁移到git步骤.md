### git author data文件
格式是这样的

```
samaxes = Samuel Santos <samaxes@example.com>
```
通过脚本命令来得到相关文件.
```bash
$ svn log ^/ --xml | grep -P "^<author" | sort -u | perl -pe 's/<author>(.*?)<\/author>/$1 = /' > authors.txt
```
---

### 创建git项目
```
$ git svn clone http://my-project.googlecode.com/svn/ --no-metadata --stdlayout --authors-file=../authors.txt my_project
```

---

### Clean up SVN references
The initial clone imports everything including SVN branches and tags, however only a master branch is available locally:

```
$ git branch
* master
```
那svn剩下的分支和tag哪里去了?

原来是 remote branch
```
$ git branch -r
  tags/v1.0
  trunk
```
So, to move the tags to be proper Git tags, run:

```
$ git for-each-ref refs/remotes/tags | cut -d / -f 4- | grep -v @ | while read tagname; do git tag "$tagname" "tags/$tagname"; git branch -r -d "tags/$tagname"; done
```
And move the rest of the references under refs/remotes to be local branches:


```
$ git for-each-ref refs/remotes | cut -d / -f 3- | grep -v @ | while read branchname; do git branch "$branchname" "refs/remotes/$branchname"; git branch -r -d "$branchname"; done

```

---
However, the local trunk branch is redundant with our Git master branch and should be removed:

```
$ git branch -d trunk
Deleted branch trunk (was e4b45d8).
```

---



### link
https://samaxes.com/2013/11/move-from-svn-to-git/
