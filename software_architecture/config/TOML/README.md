TOML Tom's Obvious, Minimal Lanuage

他的作者是 `github` 的创始人 Tom Preston-Werner

### TOML 的目标
TOML 的目标是成为一个极简的配置文件格式。TOML 被设计成可以无歧义地被映射为哈希表，从而被多种语言解析。


```toml
title = "TOML 例子"

[owner]
name = "Tom Preston-Werner"
organization = "GitHub"
bio = "GitHub Cofounder & CEO\nLikes tater tots and beer."
dob = 1979-05-27T07:32:00Z # 日期时间是一等公民。为什么不呢？

[database]
server = "192.168.1.1"
ports = [ 8001, 8001, 8002 ]
connection_max = 5000
enabled = true

[servers]

  # 你可以依照你的意愿缩进。使用空格或Tab。TOML不会在意。
  [servers.alpha]
  ip = "10.0.0.1"
  dc = "eqdc10"

  [servers.beta]
  ip = "10.0.0.2"
  dc = "eqdc10"

[clients]
data = [ ["gamma", "delta"], [1, 2] ]

# 在数组里换行没有关系。
hosts = [
  "alpha",
  "omega"
]
```
