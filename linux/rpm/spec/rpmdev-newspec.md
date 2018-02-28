您也可以使用 `rpmdev-newspec` 命令来创建 SPEC 文件。

`rpmdev-newspec 软件包名`
可以创建一个初始 SPEC 文件，该工具从软件包名判断使用哪个模板，支持指定模板。 

`/etc/rpmdevtools/spectemplate-*.spec` 包含所有可用的模板，使用 rpmdev-newspec --help 命令了解更多信息。

例如，为 python 模块创建 SPEC 文件：

```bash
cd ~/rpmbuild/SPECS
rpmdev-newspec python-antigravity
vi python-antigravity.spec
```
