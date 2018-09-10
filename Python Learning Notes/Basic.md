# 基础

## 编码

默认以 UTF-8 编码

可指定编码

```python
# -*- coding: utf-8 -*-
```

## python 保留字

Python 的标准库提供了一个 keyword 模块，可以输出当前版本的所有关键字： 

```python
import keyword
keyword.kwlist
```

```python
['False', 'None', 'True', 'and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield']
```

## 注释

单行注释 `# comment`

多行注释 `''' comment '''` 或 `""" comment """ ` 

## 多行语句

Python 通常是一行写完一条语句，但如果语句很长，我们可以使用反斜杠(\)来实现多行语句

```python
total = item_one + \
		item_two + \
		item_three
```

在 [], {}, 或 () 中的多行语句，不需要使用反斜杠(\)

```python
total = ['item_one', 'item_two', 
		'item_three']
```

## 简单输入输出

### `Print()`输出

```python
print('hello world') # 默认换行, end = '\n'
print('x', end = '') # 不换行
```

### `input()`输入

```python
temp = input("the number is ") # 输出文本提示输入
num = int(temp) # 将输入的字符串转换成对应的类型
```

## 模块导入

`import` `from ... import`

+ 整个模块导入 `import somemodule`
+ 从某个模块中导入某个函数 `from somemodule import somefunction`
+ 从某个模块中导入多个函数 `from somemodule import func1, func2, func3 `
+ 将模块中的全部函数导入 `from somemodule import *`

## 变量

+ 对大小写敏感
+ 变量名规则：可包括字母、数字、下划线，但不能以数字开头

### 标准数据类型

**不可变数据：**
+ Number (数字)
+ String (字符串)
+ Tuple (元组)

**可变数据：**
+ List (列表)
+ Set (集合)
+ Dictionary (字典)

###  判断数据类型

`type()` `isinstance()`

区别是：

+ `type()` 不会认为子类是一种父类类型 
+ `isinstance()` 会认为子类是一种父类类型 

```python
class A:
	pass
	
class B(A):
	pass
	
isinstance(A(), A)	# return True
type(A()) == A		# return True
isinstance(B(), A)	# return True
type(B()) == A		# return False
```



### 字符串(String)

+ 单行字符串可用`'str'` 或`"str"` 

+ 多行字符串可用` ''' lines ''' ` 或 ` """ lines """  `

+ **原始字符串：**  `r'C:\now' ` 使得`\`不发生转义

+ 转义符 `\`

+ 按字面意义级联字符串，如`"this " "is " "string"`会被自动转换为`"this is string" `

+ 字符串可以用 `+` 连接，用 `*` 重复

+ **两种索引方式:**  `str[index] `从左往右以0开始，从又往左以-1开始

+ 字符串不能改变

+ python没有单独的字符类型，用长度为1的字符串表示字符

+ **字符串的截取: ** `str[begin, end]` 截取到 [begin, end) 之间的字符串

```python
print(str)                 # 输出字符串
print(str[0:-1])           # 输出第一个到倒数第二个的所有字符
print(str[0])              # 输出字符串第一个字符
print(str[2:5])            # 输出从第三个开始到第五个的字符
print(str[2:])             # 输出从第三个开始的后的所有字符
print(str * 2)             # 输出字符串两次
print(str + 'hello')       # 连接字符串
```

#### 字符串格式化

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

### 数字(Number)

+ `int` (整数), 如 1, 只有一种整数类型 int，表示为长整型，没有 python2 中的 Long。
+ `bool` (布尔), 如 `True` `False`
+ `float` (浮点数), 如 1.23、3E-2
+ `complex` (复数), 如 1 + 2j、 1.1 + 2.2j

### 列表(List)

写在`[]` 里，语法基本同字符串，元素可修改

```python
list = ['abcd', 789, 2.2, 'hello', 32]

print (list)            # 输出完整列表
print (list[0])         # 输出列表第一个元素
print (list[1:3])       # 从第二个开始输出到第三个元素
print (list[2:])        # 输出从第三个元素开始的所有元素
print (list * 2)    	# 输出两次列表
print (list + list) 	# 连接列表
```

```python
a = [1, 2, 3, 4, 5, 6]
a[0] = 9 				# a = [9, 2, 3, 4, 5, 6]
a[2:5] = [13, 14, 15]	# a = [9, 2, 13, 14, 15, 6]
a[2:5] = []				# a = [9, 2, 6]
del list[2]		#删除列表元素
```

#### 内建函数&方法

函数 | 说明
--- | ---
`len(list)` | 列表元素个数
`max(list)` |返回列表元素最大值 
`min(list)` | 返回列表元素最小值
`list(seq)` | 将序列(可迭代)转换为列表 

方法 | 说明
--- | ---
`list.append(obj)` | 在列表末尾添加新的对象
`list.count(obj)` | 统计某个元素在列表中出现的次数
`list.extend(seq)` | 在列表末尾一次性追加另一个序列中的多个值（用新列表扩展原来的列表）
`list.index(obj)` | 从列表中找出某个值第一个匹配项的索引位置
`list.insert(index,obj)` | 将对象插入列表
`list.pop([index=-1])` | 移除列表中的一个元素（默认最后一个元素），并且返回该元素的值
`list.remove(obj)` | 移除列表中某个值的第一个匹配项
`list.reverse()` | 反向列表中元素
`list.sort(cmp=None, key=None, reverse=False)` | 对原列表进行排序
`list.clear()` | 清空列表
`list.copy()` | 复制列表

### 元组(Tuple)

写在`()`里，语法基本同列表，但元素不可修改

可把字符串看成特殊的元组

```python
tuple = ('abcd', 789, 2.2, 'hello', 32)

print (tuple)				# 输出完整元组
print (tuple[0])			# 输出元组的第一个元素
print (tuple[1:3])			# 输出从第二个元素开始到第三个元素
print (tuple[2:])			# 输出从第三个元素开始的所有元素
print (tuple * 2)			# 输出两次元组
print (tuple + tuple)		# 连接元组
```

#### 内建函数

函数 | 说明
--- | ---
`len(tuple)` | 元组元素个数
`max(tuple)` |返回元组元素最大值 
`min(tuple)` | 返回元组元素最小值
`tuple(seq)` | 将序列(可迭代)转换为元组 


### 集合(Set)
集合（set）是一个无序不重复元素的序列

基本功能是进行成员关系测试和删除重复元素

可以使用大括号`{ }` 或者 `set()` 函数创建集合，**注意：创建一个空集合必须用 `set()` 而不是 `{}`，因为 `{}` 是用来创建一个空字典**

```python
student = {'Tom', 'Jim', 'Mary', 'Tom', 'Jack', 'Rose'}
 
print(student)   # 输出集合，重复的元素被自动去掉
 
# 成员测试
if 'Rose' in student :
    print('Rose 在集合中')
else :
    print('Rose 不在集合中')
 
# set可以进行集合运算
a = set('abracadabra')
b = set('alacazam')
 
print(a)
print(a - b)     # a和b的差集
print(a | b)     # a和b的并集
print(a & b)     # a和b的交集
print(a ^ b)     # a和b中不同时存在的元素
```

#### 内建方法

方法 | 说明
--- | ---
`set.add(obj)` | 将元素 obj 添加到集合 set 中，如果元素已存在，则不进行任何操作
`set.update(obj)` | 同`set.add()` 
`set.remove(obj)` | 将元素 obj 添加到集合 set 中移除，如果元素不存在，则会发生错误
`set.discard(obj)` | 将元素 obj 添加到集合 set 中移除，如果元素不存在，不会发生错误
`set.pop()` | 随机删除集合中的一个元素
`set.clear()` | 清空集合set

### 字典(Dictionary)
+ 列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
+ 字典是一种映射类型，字典用`{}`标识，它是一个无序的**键(key) : 值(value)**对集合。
+ 键(key)必须使用不可变类型。
+ 在同一个字典中，键(key)必须是唯一的。

```python
dict = {}
dict['one'] = "1 - one"
dict[2]     = "2 - two"
 
tinydict = {'name': 'Job', 'age': 20, 'gender':'male'}
 
print (dict['one'])       # 输出键为 'one' 的值
print (dict[2])           # 输出键为 2 的值
print (tinydict)          # 输出完整的字典
print (tinydict.keys())   # 输出所有键
print (tinydict.values()) # 输出所有值

del tinydict['name']	# 删除键'name'
tinydict.clear()		# 清空字典
del tinydict			# 删除字典
```

使用`dict()`构建字典

```python
dict([('name','Job'),('age',20),('gender','male')])

dict(name = 'Job', age = 20, gender = 'male')

{x: x**2 for x in (2, 4, 6)} # {2: 4, 4: 16, 6: 36}
```

#### 内建函数

函数 | 说明
--- | ---
`len(dict)` | 字典元素个数
`str(dict)` | 输出字典，以可打印的字符串表示

### 类型转换

Function | illustration
--- | ---
int(x [,base]) | 将x转换为一个整数
float(x) | 将x转换到一个浮点数
complex(real [,imag]) | 创建一个复数
str(x) | 将对象 x 转换为字符串
repr(x) | 将对象 x 转换为表达式字符串
eval(str) | 用来计算在字符串中的有效Python表达式,并返回一个对象
tuple(s) | 将序列 s 转换为一个元组
list(s) | 将序列 s 转换为一个列表
set(s) | 转换为可变集合
dict(d) | 创建一个字典。d 必须是一个序列 (key,value)元组。
frozenset(s) | 转换为不可变集合
chr(x) | 将一个整数转换为一个字符
ord(x) | 将一个字符转换为它的整数值
hex(x) | 将一个整数转换为一个十六进制字符串
oct(x) | 将一个整数转换为一个八进制字符串

### 多变量赋值

```python
a = b = c = 1
a, b, c = 1,2,'string'
```



## 运算符

`>` `>=` `<` `<=` `==` `!=`  

`+` `-` `*` `/(浮点除法)` `//(整数除法)` `%(取余)` `*(乘方)`

`=` `+=` `-=` `*=` `/=` `%=` `**=` `//=`

`&` `|` `^` `~` `<<` `>>`

`and` `or` `not`

`in(如果在指定的序列中找到值返回 True，否则返回 False)` `not in`

`is(判断两个标识符是不是引用自一个对象)` `is not`



## 条件分支

## `if` `elif` `else`

**syntax** : 

```python 
if expression:
	command
elif expression:
	command
else:
	command
```

## 循环

### `while` `else`

**syntax**:

```python
while expression:
	command
else:
	command
```

### `for in ` `else`

**syntax:**

```python
for variable in sequence:
	command
else:
	command
```

### `break` `continue`

`break` 跳出循环体

`continue` 进入下一循环

### `range()`

 `range(end)` 生成 [0,end) 的数列

`range(begin,end,[step = 1])` 生成 [begin,end) 内以begin为首项，公比为step的等差数列

```python
for i in range(-10, -100, -30):
	print(i)
```

### `pass`

`pass` 是空语句，是为了保持程序结构的完整性，不做任何事情，一般用做占位语句

```python
class MyClass:
    pass

while True:
    pass # 死循环，等待键盘中断（Ctrl+C)
```

