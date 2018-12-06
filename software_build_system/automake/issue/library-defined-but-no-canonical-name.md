### 问题
```
automake: warnings are treated as errors
src/Makefile.am:3: warning: variable 'librombrowser_a_LDFLAGS' is defined but no program or
src/Makefile.am:3: library has 'librombrowser_a' as canonical name (possible typo)
autoreconf: automake failed with exit status: 1
```

### Makefile.am

```
noinst_LIBRARIES = librombrowser.a
librombrowser_a_CPPFLAGS = $(GTK_CFLAGS)
librombrowser_a_LDFLAGS = $(GTK_LIBS)
librombrowser_a_SOURCES =                                                      \
                          rombrowser-app.c                                     \
                          rombrowser-app.h                                     \
                          rombrowser-cmds-file.c                               \
                          rombrowser-cmds-help.c                               \
                          rombrowser-cmds.h                                    \
                          rombrowser-dirs.c                                    \
                          rombrowser-dirs.h                                    \
                          rombrowser-settings.c                                \
                          rombrowser-settings.h

bin_PROGRAMS = rombrowser
rombrowser_SOURCES = rombrowser.c
rombrowser_LDADD = librombrowser
```

### 解决方案

```
_LDFLAGS isn't valid for a static library, only for an executable or a shared library. 
You may want _LIBADD instead. It seems to me that the error message could be improved.
```

### note
这里需要注意的是, 如果编译的是动态链接库, 那么和静态编译的编译选项是不同的
1. xyz_LDFLAGS
2. xyz_LIBADD


### link
https://stackoverflow.com/questions/23575967/library-defined-but-no-canonical-name
