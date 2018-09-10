# 文件

`open()` 将会返回一个文件对象

**syntax:**

```python
open(filename, mode = 'r')
```

| mode | illustration                                                 |
| ---- | ------------------------------------------------------------ |
| r    | 以只读方式打开文件。文件的指针将会放在文件的开头。这是默认模式。 |
| rb   | 以二进制格式打开一个文件用于只读。文件指针将会放在文件的开头。 |
| r+   | 打开一个文件用于读写。文件指针将会放在文件的开头。           |
| rb+  | 以二进制格式打开一个文件用于读写。文件指针将会放在文件的开头。 |
| w    | 打开一个文件只用于写入。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。 |
| wb   | 以二进制格式打开一个文件只用于写入。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。 |
| w+   | 打开一个文件用于读写。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。 |
| wb+  | 以二进制格式打开一个文件用于读写。如果该文件已存在则打开文件，并从开头开始编辑，即原有内容会被删除。如果该文件不存在，创建新文件。 |
| a    | 打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。 |
| ab   | 以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。 |
| a+   | 打开一个文件用于读写。如果该文件已存在，文件指针将会放在文件的结尾。文件打开时会是追加模式。如果该文件不存在，创建新文件用于读写。 |
| ab+  | 以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。如果该文件不存在，创建新文件用于读写。 |

|    模式    |  r   |  r+  |  w   |  w+  |  a   |  a+  |
| :--------: | :--: | :--: | :--: | :--: | :--: | :--: |
|     读     |  +   |  +   |      |  +   |      |  +   |
|     写     |      |  +   |  +   |  +   |  +   |  +   |
|    创建    |      |      |  +   |  +   |  +   |  +   |
|    覆盖    |      |      |  +   |  +   |      |      |
| 指针在开始 |  +   |  +   |  +   |  +   |      |      |
| 指针在结尾 |      |      |      |      |  +   |  +   |

 ```python
f = open('test.txt','w')
f.write('Hello\nworld')
f.close()
 ```

## 文件对象的方法

Method | illustration
--- | ---
`file.close()` | 关闭文件。关闭后文件不能再进行读写操作
`file.flush()` | 刷新文件内部缓冲，直接把内部缓冲区的数据立刻写入文件, 而不是被动的等待输出缓冲区写入
`file.fileno()` | 返回一个整型的文件描述符(file descriptor FD 整型), 可以用在如os模块的read方法等一些底层操作上
`file.isatty()` | 如果文件连接到一个终端设备返回 True，否则返回 False
`file.next()` | 返回文件下一行
`file.read([size])` | 从文件读取指定的字节数，如果未给定或为负则读取所有
`file.readline([size])` | 读取整行，包括 "\n" 字符
`file.readlines([sizeint])` | 读取所有行并返回列表，若给定sizeint>0，返回总和大约为sizeint字节的行, 实际读取值可能比 sizeint 较大, 因为需要填充缓冲区
`file.seek(offset[,whence])` | 设置文件当前位置
`file.tell()` | 返回文件当前位置
`file.truncate([size])` | 从文件的首行首字符开始截断，截断文件为 size 个字符，无 size 表示从当前位置截断；截断之后后面的所有字符被删除，其中 Widnows 系统下的换行代表2个字符大小
`file.write(str)` | 将字符串写入文件，返回的是写入的字符长度
`file.writelines(sequence)` | 向文件写入一个序列字符串列表，如果需要换行则要自己加入每行的换行符。

### file.read()

`file.read(size)` 将读取一定数目的数据, 然后作为字符串或字节对象返回。 

size 是一个可选的数字类型的参数。 当 size 被忽略了或者为负, 那么该文件的所有内容都将被读取并且返回。 

```python
f = open('test.txt','r')
str = f.read()
print(str)
f.close
```

### file.readline()

`file.readline()` 会从文件中读取单独的一行。换行符为 '\n'。`file.readline()` 如果返回一个空字符串, 说明已经已经读取到最后一行。 

```python
f = open('test.txt','r')
str = f.readline()
print(str)
f.close
```

### file.readlines()

`file.readlines()` 将返回该文件中包含的所有行。

如果设置可选参数 sizehint, 则读取指定长度的字节, 并且将这些字节按行分割。

```python
f = open('test.txt','r')
strList = f.readlines()
print(strList) # strList = ['firstline\n', 'secondline\n']
f.close()
```

另一种方式是迭代一个文件对象然后读取每行:

```python
f = open('test.txt','r')
for line in f:
    print(line, end='')
f.close()
```

### file.write()

`file.write(string)` 将string写入文件中，返回写入的字符数

```python
f = open('test.txt','w')
num = f.write('hello\nworld')
print(num)
f.close()
```

如果要写入一些不是字符串的东西, 那么将需要先进行转换: 

```python
f = open('test.txt','w')
value = ('hello',14)
s = str(value) # s = '('hello', 14)'
f.write(s)
f.close()
```

### file.tell()

`file.tell()` 返回文件对象当前所处的位置，从文件头开始算字节数

### file.seek()

`file.seek(offset,from_what)` 改变当前文件的位置

`from_what`的值：0为文件开头，1为当前位置，2为文件结尾，默认为0

### file.close()

`file.close()` 关闭文件

使用`with`关键字代替,在结束后, `with`会帮你正确的关闭文件 

```python
with open('test.txt','r') as f:
    read_data = f.read()
```