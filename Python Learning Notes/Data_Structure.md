# 数据结构

## 将列表当栈使用

`append()` 添加到栈顶，`pop()` 弹出栈顶

```python
stack = [3, 4, 5]
stack.append(6)
item = stack.pop()
```

## 将列表当队列使用

`deque(list)`

```python
from collections import deque

queue = deque(['Eric','John','Michael'])
queue.append('Terry')
left = queue.popleft() # 'Eric'
right = queue.pop() # 'Terry'
```

## 列表推导式

列表可用`[]` 或`list()`

元组可用`tuple()`

集合可用`{}`或`set()`

字典可用`{}`

```python
vec = [2,4,6]
resList = [3*x for x in vec] # [6,12,18]
resList = list(3*x for x in vec)
resTuple = tuple(3*x for x in vec)
resSet = {3*x for x in vec}
resSet = set(3*x for x in vec)
resDict = {x:x**2 for x in vec}
```

```python
[[x,x**2] for x in vec] # [[2,4],[4,16],[6,36]]
```

```python
freshfruit = ['  banana', '  loganberry ', 'passion fruit  ']
freshfruit = [weapon.strip() for weapon in freshfruit] # ['banana', 'loganberry', 'passion fruit']
```

```python
[3*x for x in vec if x>3] # [12,18]
```

```python
vec1 = [2, 4, 6]
vec2 = [4, 3, -9]
[x*y for x in vec1 for y in vec2] # [8, 6, -18, 16, 12, -36, 24, 18, -54]
[x+y for x in vec1 for y in vec2] # [6, 5, -7, 8, 7, -5, 10, 9, -3]
[vec1[i]*vec2[i] for i in range(len(vec1))] # [8, 12, -54]
```

## `del`

使用 `del`语句可以从一个列表中依索引而不是值来删除一个元素。这与使用 `pop()` 返回一个值不同。可以用 `del` 语句从列表中删除一个切割，或清空整个列表 

```python
a = [1,2,3,4,5]

del a[0] # 删除一个元素 a = [2,3,4,5]
del a[1:3] # 删除[1,3)内元素 a = [2,5]
del a[:] # 清空 a = []
```

## 遍历技巧

遍历字典

```python
knights = {'gallahad': 'the pure', 'robin': 'the brave'}
for key,value in knights.items():
    print(key,value)
```

在序列中遍历时，索引位置和对应值可以使用` enumerate() `函数同时得到 

```python
list = ['tic','tac','toe']
for index,value in enumerate(list):
    print(index,value)
```

同时遍历两个或更多的序列，可以使用 zip() 组合 

```python
questions = ['name', 'quest', 'favorite color']
answers = ['lancelot', 'the holy grail', 'blue']
for q, a in zip(questions, answers):
	print('What is your {0}?  It is {1}.'.format(q, a))
```

要反向遍历一个序列，首先指定这个序列，然后调用 reversed() 函数 

```python
for i in reversed(range(1,10,2)):
    print(i)
```

要按顺序遍历一个序列，使用 sorted() 函数返回一个已排序的列表，并不修改原值 

```python
basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
for f in sorted(set(basket)):
	print(f)
```

