# 面向对象

## 类

**syntax:**

```python
class ClassName:
    pass
```

### 类的私有属性

**`__private_attrs`**：两个下划线开头，声明该属性为私有，不能在类地外部被使用或直接访问。在类内部的方法中使用时 **`self.__private_attrs`**。

### 类的方法

在类地内部，使用 `def` 关键字来定义一个方法，与一般函数定义不同，类方法必须包含参数 `self`，且为第一个参数，`self` 代表的是类的实例。

`self` 的名字并不是规定死的，也可以使用 `this`，但是最好还是按照约定是用 `self`。

#### 类的私有方法

**`__private_method`**：两个下划线开头，声明该方法为私有方法，只能在类的内部调用 ，不能在类地外部调用。**`self.__private_methods`**。

### 类的专有方法：

- **`__init__ `:** 构造函数，在生成对象时调用
- **`__del__ `:** 析构函数，释放对象时使用
- **`__repr__ `:** 打印，转换
- **`__setitem__ `:** 按照索引赋值
- **`__getitem__`:** 按照索引获取值
- **`__len__`:** 获得长度
- **`__cmp__`:** 比较运算
- **`__call__`:** 函数调用
- **`__add__`:** 加运算
- **`__sub__`:** 减运算
- **`__mul__`:** 乘运算
- **`__div__`:** 除运算
- **`__mod__`:** 求余运算
- **`__pow__`:** 乘方

#### 运算符重载

```python
class Vector:
   def __init__(self, a, b):
      self.a = a
      self.b = b
 
   def __str__(self):
      return 'Vector (%d, %d)' % (self.a, self.b)
   
   def __add__(self,other):
      return Vector(self.a + other.a, self.b + other.b)
 
v1 = Vector(2,10)
v2 = Vector(5,-2)
print (v1 + v2)
```

## 类继承

**syntax:**

```python
class DerivedClassName(BaseClassName):
    pass
```

```python
class people:
    name = '' # 公有成员
    age = 0
    __weight = 0 # 私有成员
    
    def __init__(self, n, a, w):
        self.name = n
        self.age = a
        self.__weight = w
        
    def speak(self):
        print("%s speak: I'm %d years old." %(self.name, self.age))
        
        
class student(people):
    grade = 0
    
    def __init__(self,n,a,w,g):
        people.__init__(self,n,a,w)
        self.grade = g
        
    def speak(self):
        print("%s speak: I'm %d years old, grade %d" %(self.name, self.age, self.grade))
        
if __name__ == '__main__':
    s = student('ken',10,50,3)
    s.speak()
```

### 多继承

**syntax:**

```python
class DerivedClassName(Base1, Base2, Base3):
    pass
```

### super()

调用父类

`super(BaseClassName, obj)`

```python
# 类外
s = student('ken',10,20,3)
s.speak() # 调用student类的speak()
super(people, s).speak() # 调用people类的speak()

# 类内
class Child(Parent):
    def method(self):
        super(Parent, self).method()
```



