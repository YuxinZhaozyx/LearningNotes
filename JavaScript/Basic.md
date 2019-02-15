# 语句

+ JavaScript对大小写敏感
+ JavaScript会忽略多余的空格
+ 可以在文本字符串中使用反斜杠`\`对代码行进行换行

```javascript
document.write("Hello \
World!");
```

# 注释

**单行注释**：`//`

**多行注释**：`/* */`

# 变量

```js
var x = 2;
var y = 3;
var z = x + y;
var name = "Bill", answer = 'Yes';
```

- 变量必须以字母开头
- 变量也能以 $ 和 _ 符号开头（不过我们不推荐这么做）
- 变量名称对大小写敏感（y 和 Y 是不同的变量）

```js
var name;
```

未初始化的值默认为`undefined`

# 数据类型

## 字符串

```js
var name="Bill Gates";
var name='Bill Gates';
var a = "5" + "5"; // 结果"55"
var b = "5" + 5;   // 结果"55"
```

## 数字

JavaScript只有一种数字类型。

```js
var x1=34.00;      //使用小数点来写
var x2=34;         //不使用小数点来写
var y=123e5;      // 12300000
var z=123e-5;     // 0.00123
```

## 布尔

```js
var x=true
var y=false
```

## 数组

```js
var cars = new Array();
cars[0] = "Audi";
cars[1] = "BMW";
cars[2] = "Volvo";
```

或

```js
var cars=new Array("Audi","BMW","Volvo");
```

或

```js
var cars=["Audi","BMW","Volvo"];
```

## 对象

```js
var person={
    firstname:"Bill",
    lastname:"Gates", 
    id:5566
};
```

寻址方式：

```js
name = person.lastname;
name = person['lastname'];
```

## `undefined`和`null`

`undefined` 这个值表示变量不含有值。

可以通过将变量的值设置为 `null` 来清空变量。

```js
cars = null;
person = null;
```

`null`时对象，而`undefined`不是。

```js
typeof undefined // undefined
typeof null      // object
null === undefined // false
null == undefined  // true
```

## 声明变量类型

声明新变量时，可以使用关键词 `new` 来声明其类型：

```js
var carname=new String;
var x=      new Number;
var y=      new Boolean;
var cars=   new Array;
var person= new Object;
```

JavaScript 变量均为对象。当您声明一个变量时，就创建了一个新的对象。

# 运算符

| 运算符 | 描述              | 例子     | 结果  |
| ------ | ----------------- | -------- | ----- |
| +      | 加                | x=y+2   | x=7   |
| -      | 减                | x=y-2    | x=3   |
| *      | 乘                | x=y*2    | x=10  |
| /      | 除                | x=y/2    | x=2.5 |
| %      | 求余数 (保留整数) | x=y%2    | x=1   |
| ++     | 累加              | x=++y    | x=6   |
| --     | 递减              | x=--y    |       |

| 运算符 | 例子 | 等价于 | 结果 |
| ------ | ---- | ------ | ---- |
| =      | x=y  |        | x=5  |
| +=     | x+=y | x=x+y  | x=15 |
| -=     | x-=y | x=x-y  | x=5  |
| *=     | x*=y | x=x*y  | x=50 |
| /=     | x/=y | x=x/y  | x=2  |
| %=     | x%=y | x=x%y  | x=0  |

| 运算符 | 描述             | 例子                            |
| ------ | ---------------- | ------------------------------- |
| ==     | 等于             | x==8 为 false                   |
| ===    | 全等（值和类型） | x===5 为 true；x==="5" 为 false |
| !=     | 不等于           | x!=8 为 true                    |
| >      | 大于             | x>8 为 false                    |
| <      | 小于             | x<8 为 true                     |
| >=     | 大于或等于       | x>=8 为 false                   |
| <=     | 小于或等于       | x<=8 为 true                    |

| 运算符 | 描述 | 例子                      |
| ------ | ---- | ------------------------- |
| &&     | and  | (x < 10 && y > 1) 为 true |
| \|\|   | or   | (x==5 \|\| y==5) 为 false |
| !      | not  | !(x==y) 为 true           |

**条件运算符**：

```js
variablename=(condition)?value1:value2 
```

