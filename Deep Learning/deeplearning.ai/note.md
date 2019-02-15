## numpy

### `X.sum()`

`X.sum()` 得到X中所有元素的总和

`X.sum(axis=n)` 得到`X[:][i][j]`  全部相加的新数组，即只有第axis维相加

对二维张量（矩阵）

+ `X.sum(axis=0)` 将每一列相加
+ `X.sum(axis=1)` 将每一行相加

另外的参数`keepdims`（默认为`False`）确定得到的数组是否保留原来二维特性,如

```python
X = np.array[[0, 3, 4], [1, 6, 4]]
A = X.sum(axis = 1, keepdims = False) # A = [7, 11]
A = X.sum(axis = 1, keepdims = True) # A = [[7],[11]]
```



### 广播(broadcasting)

`A = np.array([[1, 2, 3, 4],[1, 2, 3, 4]])` 

`A + 1 = [[2, 3, 4, 5],[2, 3, 4, 5]]` 加实数相当于每一项加该实数

`A + [[1],[2]] = [[2,3,4,5],[3,4,5,6]]  ` 加行或列向量会自动复制再相加

`[[1, 2], [3, 4]] * [1, 2] = [[1,  4], [3, 8]]` 实现对应元素相乘，点乘需用`np.dot()`

### 调试

`assert(A.shape==(5,1))`

用`np.reshape()`将`shape == (5,)` 的向量转成 `shape == (5, 1)`

shape为`(5,)`型的向量同时作为行向量或列向量，如`np.dot(A, A)`等同于$ A^T \cdot A $ ，能够得到正确值

但shape为(5,1)型的向量`np.dot(A, A)`将由于大小都为(5,1)不能点乘而报错

建议尽量避免用`(5,)`型的向量

### `X.reshape()`

`X.reshape()`返回修改维度后的数组，但X本身不变

### 标准化

For example, if $$x = 
\begin{bmatrix}
    0 & 3 & 4 \\
    2 & 6 & 4 \\
\end{bmatrix}$$ then 
$$
\| x\| = np.linalg.norm(x, axis = 1, keepdims = True) = \begin{bmatrix}
    5 \\
    \sqrt{56} \\
\end{bmatrix}
$$

and        

$$
x\_normalized = \frac{x}{\| x\|} = \begin{bmatrix}
    0 & \frac{3}{5} & \frac{4}{5} \\
    \frac{2}{\sqrt{56}} & \frac{6}{\sqrt{56}} & \frac{4}{\sqrt{56}} \\
\end{bmatrix}
$$

 Note that you can divide matrices of different sizes and it works fine: this is called broadcasting and you're going to learn about it in part 5.

### 范数

`np.linalg.norm(x, ord = None, axis = None, keepdims = False)`

x: 表示矩阵（也可以是一维的）

ord：范数

| ord                | 说明     | 计算方法                                                 |
| ------------------ | -------- | -------------------------------------------------------- |
| ord = None（默认） | 二范数   | $\sqrt{x_1^2+x_2^2+...+x_n^2}$                           |
| ord = 2            | 二范数   | 同上，但要求x必须为array like， ord=None不要求array like |
| ord = 1            | 一范数   | $|x_1!+|x_2|+...+|x_n|$                                  |
| ord = np.inf       | 无穷范数 | $max(|x_i|)$                                             |

axis: 指定维度

+ axis=1表示按行向量处理，求多个行向量的范数

+ axis=0表示按列向量处理，求多个列向量的范数

+ axis=None表示矩阵范数

keepdims： 是否保留矩阵的二位特性，否则直接转成普通的array

### 展开为一维

`np.ravel()`和`np.flatten()`都是将多维数组转为一维(n,)的形式。但`np.flatten()`返回原数组的副本，而`np.ravel()`返回的是视图(view)，即修改`np.ravel()`的内容会影响原数组。

```python
A = np.ravel(Y)
A = np.flatten(Y)
A = Y.ravel()
A = Y.flatten()
```

### 随机张量

`numpy.random.randn(d0, d1, …, dn)`是从标准正态分布中返回一个或多个样本值。 
`numpy.random.rand(d0, d1, …, dn)`的随机样本位于[0, 1)中。 



## 符号约定

$X$ 表示输入矩阵 shape = (n, m), n为每个样本的特征数，m为样本个数

$Y​$ 表示label shape = (1, m)

$X^{(i)}$ 表示第$i$个样本的向量 shape = (n, 1)

$X^{(i)}_j$ 表示第$i$个样本第j项的值 scalar 

$A^{[i]}$ 表示第$i$层的输出，记$A^{[0]} = X^{(i)}$

$W^{[i](j)}$ 表示第j个样本在第i层的权重



 