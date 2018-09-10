# 基本操作与矩阵

## 基本操作

### 运算符优先级

()  >  ^  >  *, /  >  +,-

### 特殊变量

i,j : complex number

Inf: ∞ 

eps: 2.2204e-016

NaN: not a number

pi: π

### Matlab调用优先级

由高到低

​	Variable

​	Built-in function

​	Subfunction

​	Private function:

​		MEX-file

​		P-file

​		M-file

### 指令

`help 函数名` 显示指定函数的简要说明

`clear 变量名` 清除该变量

`who` 显示工作区的变量

`whos` 显示工作区中变量的信息

`clc` 清空屏幕

`format 显示模式` 调整数值的显示模式

显示模式 | 说明 
--- | ---
short (默认) | 小数点后4位
long | 小数点后15位
shortE | 科学记数法short
longE | 科学记数法long
bank | 当前格式保留小数点后2位
hex | 16进制
rat | 分数



## Array (Vector and Matrix)

行向量: ` a = [1 2 3 4] `

列向量: ` b = [1; 2; 3; 4]`

 矩阵: ` c = [1 2 3; 4 5 6; 7 8 9]`

`...` 表示换行

```matlab
d = [1 2 3; ...
	4 5 6; ...
	7 8 9]
```



### Array Indexing

方法一：` A(index)`  按列由1开始索引

例：`A(8)`  `A([1 3 5])`  `A([1 3; 1 3])`

方法二：`A(row, column)` 按行和列索引

例：`A(3,2)` `A([1 3], [1 3])`

### Colon Operator

建立等差的数组

Syntax | illustration
--- | ---
`j:k` | `[j, j+1, j+2,  ... , j+m]`
`j:i:k` | `[j, j+i, j+2i, ..., j+m*i]`

例：

` B = 1:5` => ` B = [1 2 3 4 5]`

` B = 1:2:5` => `B = [1 3 5]`

`B = 1:2:4` => `B = [1 3]`

`B = [1:5; 2:3:15; -2:0.5:0]` => `B = [1 2 3 4 5; 2 5 8 11 14; -2 -1.5 -1 -0.5 0]`

`str = 'a': 2: 'z' ` => ` str = 'acegikmoqsuwy' `



colon作为索引表示全部

例:

`A(3, :)` 表示第三行的向量

`A(3, :) = []` 表示去除该行



### 矩阵合并

`A = [1 2; 3 4]` `B = [5 6; 7 8]` `F = [A B]`

### 矩阵运算

`A = [1 2 3; 4 5 6; 7 8 9]`
`B = [3 4 5; 6 7 8; 1 2 3]`
`a = 2`


Operation | illustration
--- | ---
`C=A+a` |  每个元素+a
`C=A+B` | 对应元素相加
`C=A*B` | 叉乘
`C=A.*B` | 点乘
`C=A/B` | 矩阵除法
`C=A./B` | 对应元素相除
`C=A/a` | 每个元素/a
`C=A./a` | 同A/a
`C=A^a` | A叉乘自己(a-1)次
`C=A.^a` | 每个元素^a
`C=A'` | 矩阵转置 

### 特殊矩阵

`eye(n)` : n*n 单位矩阵

`zeros(row, column)` ：row*column 零矩阵

`ones(row, column)` ：row*column 所有元素均为1的矩阵

`diag([2 3 4])` ：对角矩阵

`linspace(0, 13, 6)` : 线性插值向量，第一个元素为0，最后一个元素为13，共6个元素

### 矩阵相关函数

`inv(A)` : 逆矩阵

`det(A)` : 行列式

`adj(A)` : 伴随矩阵

`cond(A)` : Matrix condition number 

`rank(A)` : 矩阵的秩

`max(A)` : 找到每一列最大值组成一个行向量

`min(A)` : 找到每一列最小值组成一个行向量

`sum(A)` : 每列相加组成一个行向量

`mean(A)` : 每列均值组成一个行向量

`sort(A)` : 每列排序返回矩阵

`sortrows(A)` : 根据每行第一个元素对行排序返回矩阵

`size(A)` : 返回 row 和 column。`size(A,1)`返回row，`size(A,2)` 返回column

`length(A)` ：返回 row*column

`find(expression)` : 找到满足expression的元素的索引组成列向量，如`find(A==value)` 找到A中值为value的元素的索引组成列向量

### reshape()

```matlab
A = [1 2; 3 4];
B = reshape(A,1,4); % B=[1 2 3 4]
```










