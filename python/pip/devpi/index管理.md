### create index
```
devpi index -c dev bases=root/pypi
```

create a “dev” index, telling it to use the root/pypi cache as a base so that all of pypi.org packages will appear on that index.

创建一个 `dev` index, 该index继承自`root/pypi`, 所有pypi.org都可以被这个索引使用.



---


### use index
```
devpi use testuser/dev
```

We are now ready to go for uploading and testing packages.

