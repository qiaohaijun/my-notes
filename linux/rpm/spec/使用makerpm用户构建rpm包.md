
### 切记！

不要使用 root 用户来执行打包操作。因为这十分危险，所有二进制文件都会在打包前安装至系统中，因此您应该以普通用户身份打包，以防止系统被破坏。

创建名为 makerpm 的用户，添加至 'mock' 用户组，设置好密码并通过该用户登录：


```bash
 # /usr/sbin/useradd makerpm
 # usermod -a -G mock makerpm
 # passwd makerpm
```

然后，您可以通过这个临时用户开始打包操作。

一旦以 makerpm 用户登陆，使用以下命令在用户家目录下，创建标准的打包工作目录结构：

```bash
 $ rpmdev-setuptree
```
