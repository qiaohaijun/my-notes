今天在打包项目的时候, 发现打包的效果出乎意料, 比正常的包大了4倍, 仔细查找了一下, 发现原来是`.git`目录下的文件加进了tar包中.

### exclude选项不work
```
tar -cvzj abc.tar.gz ./abc --exclude .git

```

可能是隐藏文件的问题, 导致tar看不到`.git`

### exclude-vcs

把 exclude替换为exclude-vcs, 问题解决了.
