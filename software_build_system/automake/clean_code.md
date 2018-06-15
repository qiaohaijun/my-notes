对于automake来说它会自动的生成很多的文件出来.
1. Makefile.in
2. Makefile
3. config.status
4. config-dump.h
5. ...


### 遇到的坑
编译出来的代码的api接口和需求的不一致. 最后发现时因为没有彻底的删除掉自动生成的文件导致的.

### trick
写脚本递归的遍历不同的子目录.
