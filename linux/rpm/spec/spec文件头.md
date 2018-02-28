一般的spec文件头包含以下几个域

注意大小写

### Summary

### Name

### Version

### Release

### Vendor

### Copyright

### Group


### Source

源代码包, 可以带多个. 使用


1. Source1; 在后面使用%{Source1}引用
2. Source2; 在后面使用%{Source2}引用
3. ... ...

注意

`Source` == `Source0`

---


### Patch

补丁源码, 如`Source`可以有多个
1. Patch1
2. Patch0
3. ... ...
