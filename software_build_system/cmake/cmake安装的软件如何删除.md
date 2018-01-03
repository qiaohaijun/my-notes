找到make install之后产生的这个文件install_manifest.txt
里面有安装的所有东西的路径，删除它们即可。

**参考命令：**
```bash
cat install_manifest.txt | sudo xargs rm 
```
