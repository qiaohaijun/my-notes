补丁文件名通常像这样 "telnet-0.17-env.patch"，命名格式为 %{name} - %{version} - REASON.patch"（有时省略 version 版本）。
补丁文件通常是 "diff -u" 命令的输出；
如果你在 ~/rpmbuild/BUILD 子目录执行此命令，则之后便不需要指定 -p 选项。


### REF
- https://fedoraproject.org/wiki/How_to_create_an_RPM_package/zh-cn
