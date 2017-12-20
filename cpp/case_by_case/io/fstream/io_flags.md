1. ios::in
2. ios::out
3. ios::binary
4. ios::ate
5. ios::app
6. ios::trunc

** ios::in
open for input operations

** ios::out
open for output operations

** ios::binary
open in binary mode

** ios::ate
1. set the initial poistion at the end of the file
2. if this flag is not set to any value, the initial postion is the begining of the file

** ios::app
1. all output operations are performed at the end of the file, appending the content to the current content of the file.
2. this flag can only be used in streams open for output-only operations

** ios::trunc
if the file opened for output operations already existed before, iths previous content is deleted and replaced by the new one.

---

我觉的这些api设计有问题
1. 不一致, binary vs app, 如果追求一致性, 那么是不是应该使用bin 而不是 binary
2. 语义不清楚, 比如ate, app
3. 使用了太多的缩写, 比如 app, 
