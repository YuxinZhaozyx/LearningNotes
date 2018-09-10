# 输入与输出

## str() & repr()

如果你希望将输出的值转成字符串，可以使用 repr() 或 str() 函数来实现 

- **str()：** 函数返回一个用户易读的表达形式。
- **repr()：** 产生一个解释器易读的表达形式。

```python
# repr() 可以转义字符串中的特殊字符
s = 'hello\n'
repr(s) # "'hello\\n'"
# repr() 的参数可以是Python的任何对象
x = 32.5
y = 40000
repr((x,y,('Google','Runoob'))) #(32.5,40000,('Google','Runoob'))
```

## str.format() 字符串格式化

`{}` 配合`.format()`

**方法一：**

`{}`内无任何东西，按顺序填入

```python
print('{} and {}'.format('Job', 'John')) # Job and John
```

**方法二：**

`{}`内加入索引值

```python
print('{0} and {1}'.format('Job', 'John')) # Job and John
print('{1} and {0}'.format('Job', 'John')) # John and Job
```

**方法三：**

`{}`内加入关键字参数

```python
print('{name1} and {name2}'.format(name1 = 'Job', name2 = 'John')) # Job and John
```

**另：**

`!a` (使用 `ascii()`), `!s` (使用 `str()`) 和 `!r` (使用 `repr()`) 可以用于在格式化某个值之前对其进行转化: 

```python
import math
print('常量 PI 的值近似为： {}。'.format(math.pi)) # 常量 PI 的值近似为： 3.141592653589793。
print('常量 PI 的值近似为： {!r}。'.format(math.pi)) # 常量 PI 的值近似为： 3.141592653589793。
```

可选项 `:` 和格式标识符可以跟着字段名。 这就允许对值进行更好的格式化。

```python
import math
print('常量 PI 的值近似为 {0:.3f}。'.format(math.pi))
# 常量 PI 的值近似为 3.142。
```

在 `:` 后传入一个整数, 可以保证该域至少有这么多的宽度。 用于美化表格时很有用。 

```python
table = {'Anne': 1, 'John': 2, 'Tom': 3}
for name, number in table.items():
	print('{0:10} ==> {1:10d}'.format(name, number))
	
"""
Anne     ==>          1
John     ==>          2
Tom      ==>          3
"""
```

传入一个字典, 然后使用方括号 `[]` 来访问键值 : 

```python
table = {'Anne': 1, 'John': 2, 'Tom': 3}
print('Anne: {0[Anne]:d}; John: {0[John]:d}; Tom: {0[Tom]:d}'.format(table))
# Anne: 1; Google: 2; Tom: 3
```

也可以通过在 table 变量前使用 `**` 来实现相同的功能 

```python
table = {'Anne': 1, 'John': 2, 'Tom': 3}
print('Anne: {Anne:d}; John: {John:d}; Tom: {Tom:d}'.format(**table))
# Anne: 1; John: 2; Tom: 3
```

## 旧式字符串格式化

```python
print ("I'm %s, %d years old." %('Job', 20))
```

格式化操作符 | 说明
--- | ---
%c | 格式化字符及其ASCII码
%s | 格式化字符串
%d | 格式化整数
%u | 格式化无符号整型
%o | 格式化无符号八进制数
%x | 格式化无符号十六进制数
%X | 格式化无符号十六进制数（大写）
%f | 格式化浮点数字，可指定小数点后的精度
%e | 用科学计数法格式化浮点数
%E | 作用同%e，用科学计数法格式化浮点数
%g | %f和%e的简写
%G | %f 和 %E 的简写
%p | 用十六进制数格式化变量的地址

格式化操作符辅助指令 | 说明
--- | ---
`*` | 定义宽度或者小数点精度
`-` | 用做左对齐
`+` | 在正数前面显示加号( + )
`<sp>` | 在正数前面显示空格
`#` | 在八进制数前面显示零('0')，在十六进制前面显示'0x'或者'0X'(取决于用的是'x'还是'X')
`0` | 显示的数字前面填充'0'而不是默认的空格
`%` | `%%`输出一个单一的`%`
`(var)` | 映射变量(字典参数)
`m.n.` | m 是显示的最小总宽度,n 是小数点后的位数(如果可用的话)

## 读取键盘输入

`input()`

```python
str = input("the number is ") # 输出文本提示输入
num = int(str) # 将输入的字符串转换成对应的类型
```

## 读写文件

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

### 文件对象的方法

#### file.read()

`file.read(size)` 将读取一定数目的数据, 然后作为字符串或字节对象返回。 

size 是一个可选的数字类型的参数。 当 size 被忽略了或者为负, 那么该文件的所有内容都将被读取并且返回。 

```python
f = open('test.txt','r')
str = f.read()
print(str)
f.close
```

#### file.readline()

`file.readline()` 会从文件中读取单独的一行。换行符为 '\n'。`file.readline()` 如果返回一个空字符串, 说明已经已经读取到最后一行。 

```python
f = open('test.txt','r')
str = f.readline()
print(str)
f.close
```

#### file.readlines()

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

#### file.write()

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

#### file.tell()

`file.tell()` 返回文件对象当前所处的位置，从文件头开始算字节数

#### file.seek()

`file.seek(offset,from_what)` 改变当前文件的位置

`from_what`的值：0为文件开头，1为当前位置，2为文件结尾，默认为0

#### file.close()

`file.close()` 关闭文件

使用`with`关键字代替,在结束后, `with`会帮你正确的关闭文件 

```python
with open('test.txt','r') as f:
    read_data = f.read()
```

## picklem模块

python的pickle模块实现了基本的数据序列和反序列化。

通过pickle模块的序列化操作我们能够将程序中运行的对象信息保存到文件中去，永久存储。

通过pickle模块的反序列化操作，我们能够从文件中创建上一次程序保存的对象。

```python
pickle.dump(obj, file, [,protocol]) # 写入文件
```

```python
obj = pickle.load(file) # 读出
```

```python
import pickle

data = {'a': [1, 2.0, 3, 4+6j],
       	'b': ('String',u'Unicode string'),
       	'c': None}

output = open('data.pkl','wb')
pickle.dump(data,output)
output.close()

input = open('data.pkl','rb')
data = pickle.load(input)
print(data)
```







