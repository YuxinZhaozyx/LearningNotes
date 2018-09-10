# 线性回归方程

## 线性方程式

$$
Linerar \, equation:\begin{cases} 3x - 2y = 5 \\ x + 4y = 11\end{cases} \\ 
Matrix \,notation: \begin{bmatrix} 3 & -2 \\ 1 & 4 \end{bmatrix} \begin{bmatrix} x \\ y\end{bmatrix} = \begin{bmatrix} 5 \\ 11 \end{bmatrix}
$$

### 高斯消去法

`rref()`

```matlab
A = [3 -2; 1 4];
b = [5; 11];
R = rref([A b])
% 得到的矩阵为
% R = [1 0 3;
%	   0 1 2]
```

### LU 因式分解法

将 $ Ax = b $ 中的 $ A $ 分解为 $ PA = LU $ ，其中$ L, U$ 为两个三角矩阵，$ P $ 为置换矩阵，令 $ y = Ux $ , 则 $ PAx = LUx = Pb $ ，由于 $ L,U $ 满秩，必存在 $ L^{-1},U^{-1} $ ，最终结果: $ x = U^{-1}L^{-1}Pb $

使用函数： `lu()`

```matlab
A = [1 1 1; 2 3 5; 4 6 8];
b = [2; 7; 3];
[L U P] = lu(A);
x = inv(U)*inv(L)*P*b
```

#### 其他分解函数

Matrix Decomposition Function | illustration
--- | ---
qr | Orthogonal-triangular decomposition
ldl | Block LDL' factorization for Hermitian indefinite matrices
ilu | Sparse incomplete LUU factorization
lu | LU matrix factorization
chol | Cholesky factorization
gsvd | Generalized singular value decomposition
svd | Singular value decomposition

 ### 矩阵左除

`\` 或 `mldivide()`

```matlab
A = [1 1 1; 2 3 5; 4 6 8];
b = [2; 7; 3];
x = A\b
```

### 克拉默法则 Cramer's (Inverse) Method

$$
Ax = b \Rightarrow x = A^{-1}b \Rightarrow x = \frac{A^*}{|A|}b \\ 若|A| =0，则 A^{-1}不存在，此方法无效
$$

$ |A| $ 可由 `det(A)` 得到, $ A^* $ 可由 `adj(A)` 得到.

```matlab
A = [1 1 1; 2 3 5; 4 6 8];
b = [2; 7; 3];
x = inv(A)*b
```



## 线性系统

$$
y = Ab
$$

find vector(s) $ v_i $ such that
$$
Av_i = \lambda_i v_i
$$
Then decompose 
$$
b = \sum \alpha_i v_i \quad \alpha_i \in R \\
y = Ab = A \sum \alpha_i v_i = \sum \alpha_i A v_i = \sum \alpha_i \lambda_i v_i
$$
`eig()` ：求特征值和特征向量

```matlab
A = [2 -12; 1 -5];
[V D] = eig(A); % 返回特征值的对角矩阵D和矩阵V，其列是对应的右特征向量，使得 A*V = V*D
```





