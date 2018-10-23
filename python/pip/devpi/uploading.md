
#### 使用uploading功能, 首先要登陆你的账号.
```
devpi login testuser --password=123
```

#### 查看current devpi index

```bash
#devpi use
current devpi index: http://localhost:3141/qiaohaijun/sogo (logged in as qiaohaijun)
/root/.pip/pip.conf    : no config file exists
~/.pydistutils.cfg     : no config file exists
~/.buildout/default.cfg: no config file exists
```

### 上传 wheel格式的数据 pkg
```
devpi upload --formats bdist_wheel tensorflow-1.11.0rc1-cp27-cp27mu-linux_x86_64.whl 
```
