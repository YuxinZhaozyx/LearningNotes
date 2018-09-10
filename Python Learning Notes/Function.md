# 函数

**syntax:**

```python
def function(parameter):
	body
```

参数传递：

+ 不可变参数：fun(a)内部修改a的值不会影响a本身
+ 可变参数：fun(a)内部修改a的值会影响a本身

## 默认参数

```python
def printInfo( name, age = 35):
	print("name: ", name)
	print("age: ",  age)
	return
	
printInfo( age = 20, name = 'Job')
printInfo( name = 'Tom')
printInfo('Anne')
```

## 不定长参数

+ 加了`*`的参数会以元组(tuple)的形式导入，存放所有未命名的变量参数

**syntax:**

```python
def function([formal_args,] *var_args_tuple):
	function_suite
```

```python
def printInfo(arg, *vartuple):
	print(arg)
	for var in vartuple:
		print(var)

printInfo(3,2,1)
```

+ 加了 `**` 的参数会以字典(Dictionary)的形式导入

**syntax:**

```python
def function([formal_args,] **var_args_dict):
	function_suite
```

```python
def printInfo(arg, **vardict):
	print(arg)
	print(vardict)
	
printinfo(1, a=2, b=3)
```

+ 如果单独出现星号 `*` 后的参数必须用关键字传入

```python
def f(a,b,*,c):
	return a+b+c
	
f(1,2,3) # 报错
f(1,2, c=3) # 正确用法
```

## 匿名函数 lambda

**syntax:**

```python
lambda [arg1 [, arg2, ...argn]]:expression
```

```python
sum = lambda arg1, arg2: arg1 + arg2

print(sum(10,30))
```

## 变量作用域

Python的作用域共4个：

+ L (Local)  局部作用域
+ E (Enclosing) 闭包函数外的函数中
+ G (Global) 全局作用域
+ B (Built-in) 内建作用域

以L,E,G,B的顺序去查找

```python
x = int(2.9) # B

g_count = 0 # G
def outer():
	o_count = 1 # E
	def inner():
		i_count = 2 # L
```

### `global` `nonlocal`

当内部作用域想修改外部作用域的变量时，就要用到`global`和`nonlocal`关键字了

```python
num = 1
def fun1():
    global num  # 需要使用 global 关键字声明
    print(num) 
    num = 123
    print(num)
fun1()
print(num)
```

```python
def outer():
    num = 10
    def inner():
        nonlocal num   # nonlocal关键字声明
        num = 100
        print(num)
    inner()
    print(num)
outer()
```



