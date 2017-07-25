###　两种文件 IO
1. 流式文件操作
2. IO文件操作

#### 流式文件操作
1. 流式文件操作通过缓冲区来进行
2. 流式文件读取通过 FILE指针来进行


```c
typedef struct {
int level; /* fill/empty level of buffer */
unsigned flags; /* File status flags */
char fd; /* File descriptor */
unsigned char hold; /* Ungetc char if no buffer */
int bsize; /* Buffer size */
unsigned char _FAR *buffer; /* Data transfer buffer */
unsigned char _FAR *curp; /* Current active pointer */
unsigned istemp; /* Temporary file indicator */
short token; /* Used for validity checking */
} FILE;    /* This is the FILE object */
```

#### io 文件操作

1. 通过直接存/取文件来完成文件的处理
2. 直接IO通过围绕一个句柄操作符来进行 又称作 文件描述符

---


#### 操作 FILE 结构体的函数

1. fopen() 打开流
2. fclose() 关闭流
3. fputc() 写一个字符到流里
4. fgetc() 从流中读出一个字符
5. fseek() 在流中定位到指定的字符
6. fputs() 写字符串到流
7. fgets() 从流中读出一行或者指定个字符
8. fprintf() 按格式输出到流
9. fscanf() 从流中而按照格式读取
10. feof() 到达文件尾时候返回真值
11. rewind() 复位到文件定位器到文件开始的地方
12. remove() 删除文件
13. fread() 从流中读出指定个数的字符
14. fwrite() 向流中写入指定个数的字符
15. tmpfile() 生成一个临时文件
16. tmpnam() 生产一个唯一的文件名


---

### 详细介绍

#### fopen()
```c
FILE * fopen(const char * filename, const char *mode)
```
**open 实现了三个功能**
1. 打开一个流
2. 把一个文件和这个流相连接
3. 给这个流返回 FILE指针

---

mode 的内容

- r+ 打开可读写的文件，该文件必须存在。
- rb+ 读写打开一个二进制文件，只允许读写数据。
- rt+ 读写打开一个文本文件，允许读和写。
- w 打开**只写**文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
- w+ 打开可**读写**文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
-　a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
- a+ 以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
- wb 只写打开或新建一个二进制文件；只允许写数据。
- wb+ 读写打开或建立一个二进制文件，允许读和写。
- wt+ 读写打开或着建立一个文本文件；允许读写。
- at+ 读写打开一个文本文件，允许读或在文本末追加数据。
- ab+ 读写打开一个二进制文件，允许读或在文件末追加数据。

##### 文本进制模式的区别
1. 文本模式中，一个回车会被处理为 '\n'
2. 二级制模式中，会被认为是字符Ox0D,Ox0A
3. 如果在文件中读到0x1B,文本模式会认为是文件结束符，但是二进制不会这么干

 
 ```c
 FILE * pFile;
 pFile = fopen("123.456","wb")
 ```
 pFile 在这里 p 表示 pointer，指针的意思
 
 


---


#### fclose()

```c
int fclose(FILE *fp)
```

1. 成功返回0
2. 失败返回EOF

结束的时候，请删除文件，不然会导致不可预料的问题

---

#### fputc()
