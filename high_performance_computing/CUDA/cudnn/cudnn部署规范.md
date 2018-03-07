```
[@nmyjs_176_98 local]# tree cudnn-6.0.21/
cudnn-6.0.21/
├── include
│   └── cudnn.h
└── lib64
    ├── libcudnn.so -> libcudnn.so.6
    ├── libcudnn.so.6 -> libcudnn.so.6.0.21
    ├── libcudnn.so.6.0.21
    └── libcudnn_static.a

```

### 部署位置
```
/usr/local/
```

### 命名规范
```
cudnn-6.0.21
```

### 项目架构
- `include` 包含`cudnn.h`
- `lib64` 包含具体的代码

---

### 举一反三
- cudnn-5.1.10
