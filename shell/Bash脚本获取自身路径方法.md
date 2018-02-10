### bash 获取路径的一些局限

```
pwd
```

`pwd`可以获取脚本执行的路径, 而不能获取脚本的存放地址.

```
# /home/user/scripts/getmydir.sh
MYDIR=`pwd`
echo ${MYDIR}
```

1. 在/home/user/scripts目录下执行./getmydir.sh得到脚本所在的绝对路径。
2. 但如果该脚本在其他目录下执行，比如在/home/user下执行scripts/getmydir.sh 得到的路径却是/home/user/。


```bash
# /home/user/scripts/getmydir2.sh
MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
```


### BASH_SOURCE 环境变量



### link
- http://metman.info/blog/2014/11/05/bashjiao-ben-huo-qu-zi-shen-lu-jing-fang-fa/
