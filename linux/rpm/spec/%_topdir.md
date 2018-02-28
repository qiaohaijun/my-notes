目录名	| 说明 | macros中的宏名
--- | --- | ---
BUILD	| 编译rpm包的临时目录 | %_builddir
BUILDROOT | 编译后生成的软件临时安装目录 | %_buildrootdir
RPMS | 最终生成的可安装rpm包的所在目录 | %_rpmdir
SOURCES | 所有源代码和补丁文件的存放目录	| %_sourcedir
SPECS	| 存放SPEC文件的目录(重要) |	%_specdir
SRPMS | 软件最终的rpm源码格式存放路径(暂时忽略掉，别挂在心上)	| %_srcrpmdir


### rpmdev-setuptree

执行 rpmdev-setuptree 会在当前用户家目录下的rpmbuild目录(如果该目录不存在也会被自动创建)里自动建立上述目录。 
