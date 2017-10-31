### With语句是什么？

> Python’s with statement provides a very convenient way of dealing with the situation where you have to do a setup and teardown to make something happen. 
A very good example for this is the situation where you want to gain a handler to a file, 
read data from the file and the close the file handler.

有一些任务，可能事先需要设置，事后做清理工作。
对于这种场景，Python的with语句提供了一种非常方便的处理方式。
一个很好的例子是文件处理，你需要获取一个文件句柄，从文件中读取数据，然后关闭文件句柄。

> Without the with statement, one would write something along the lines of:
如果不用with语句，代码如下：

```python
file = open("/tmp/foo.txt")
data = file.read()
file.close()
```

> There are two annoying things here. 
First, you end up forgetting to close the file handler. 
The second is how to handle exceptions that may occur once the file handler has been obtained. 
One could write something like this to get around this:

这里有两个问题。一是可能忘记关闭文件句柄；二是文件读取数据发生异常，没有进行任何处理。下面是处理异常的加强版本：

```python
file = open("/tmp/foo.txt")
try:
    data = file.read()
finally:
    file.close()
```

> While this works well, it is unnecessarily verbose. 
This is where with is useful. 
The good thing about with apart from the better syntax is that it is very good handling exceptions. 
The above code would look like this, when using with:

虽然这段代码运行良好，但是太冗长了。
这时候就是with一展身手的时候了。
除了有更优雅的语法，with还可以很好的处理上下文环境产生的异常。下面是with版本的代码：


```python
with open("/tmp /foo.txt") as file:
    data = file.read()
```


### with 原理
> while this might look like magic, the way Python handles with is more clever than magic. 
The basic idea is that the statement after with has to evaluate an object that responds to an 
__enter__() as well as an __exit__() function.

这看起来充满魔法，但不仅仅是魔法，Python对with的处理还很聪明。
基本思想是with所求值的对象必须有一个__enter__()方法，一个__exit__()方法。


> After the statement that follows with is evaluated, 
the __enter__() function on the resulting object is called. 
The value returned by this function is assigned to the variable following as. 
After every statement in the block is evaluated, the __exit__() function is called.

紧跟with后面的语句被求值后，返回对象的__enter__()方法被调用，这个方法的返回值将被赋值给as后面的变量。
当with后面的代码块全部被执行完之后，将调用前面返回对象的__exit__()方法。


> This can be demonstrated with the following example:

下面例子可以具体说明with如何工作：

```python
#!/usr/bin/env python
# with_example01.py

class Sample:
    def __enter__(self):
        print "In __enter__()"
        return "Foo"

    def __exit__(self, type, value, trace):
        print "In __exit__()"

            
def get_sample():
    return Sample()


with get_sample() as sample:
    print "sample:", sample
```
> When executed, this will result in:

行代码，输出如下

```bash
bash-3.2$ ./with_example01.py
In __enter__()
sample: Foo
In __exit__()
```

正如你看到的，
1. __enter__()方法被执行
2. __enter__()方法返回的值 - 这个例子中是”Foo”，赋值给变量’sample’
3. 执行代码块，打印变量”sample”的值为 “Foo”
4. __exit__()方法被调用

with真正强大之处是它可以处理异常。
可能你已经注意到Sample类的__exit__方法有三个参数- val, type 和 trace。 
这些参数在异常处理中相当有用。
我们来改一下代码，看看具体如何工作的。

```python
#!/usr/bin/env python
# with_example02.py


class Sample:
    def __enter__(self):
        return self

    def __exit__(self, type, value, trace):
        print "type:", type
        print "value:", value
        print "trace:", trace
        
    def do_something(self):
        bar = 1/0
        return bar + 10

with Sample() as sample:
    sample.do_something()
```

这个例子中，with后面的get_sample()变成了Sample()。
这没有任何关系，只要紧跟with后面的语句所返回的对象有 __enter__()和__exit__()方法即可。
此例中，Sample()的__enter__()方法返回新创建的Sample对象，并赋值给变量sample。

```bash
bash-3.2$ ./with_example02.py
type: <type 'exceptions.ZeroDivisionError'>
value: integer division or modulo by zero
trace: <traceback object at 0x1004a8128>
Traceback (most recent call last):
  File "./with_example02.py", line 19, in <module>
    sample.do_somet hing()
  File "./with_example02.py", line 15, in do_something
    bar = 1/0
ZeroDivisionError: integer division or modulo by zero
```
实际上，在with后面的代码块抛出任何异常时，__exit__()方法被执行。
正如例子所示，异常抛出时，与之关联的type，value和stack trace传给__exit__()方法，因此抛出的ZeroDivisionError异常被打印出来了。
开发库时，清理资源，关闭文件等等操作，都可以放在__exit__方法当中。






