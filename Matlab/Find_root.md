# 方程组求根

## 解析解 Symbolic Root Finding Approach

### 解方程

使用symbolic variables, 需用`sym`或`syms`创建 symbolic variables.

使用 `solve()` 求解 y=0 (可能得到复数解)

```matlab
syms x % 或 x = sym('x')
y = x*sin(x)-x; 
solve(y,x) % 或 solve('x*sin(x)-x',x)
```

带未知常数的方程

```matlab
syms x a b
y = a*x^2-b;
solve(y,x)
```

### 解方程组

```matlab
syms x y
eq1 = x - 2*y -5;
eq2 = x + y - 6;
A = solve(eq1,eq2,x,y);
A.x
A.y
```

求 $ A = \begin{bmatrix} a & b \\ c & d \end{bmatrix} $ 的逆矩阵 $ B = \begin{bmatrix} e & f \\ g & h \end{bmatrix} = inv(A) $ 

```matlab
syms a b c d e f g h
A = [a b; c d];
B = [e f; g h];
E = eye(2,2);
F = A*B-E;
Ans = solve(F,e,f,g,h);
B_Ans = [Ans.e Ans.f; Ans.g Ans.h]
```

### 求微分表达式

使用函数：`diff()`

```matlab
syms x
y = 4*x^5;
yprime = diff(y); % y = 5*x^4
```

```matlab
syms x y
f = x*y;
% f的一阶偏导数
df_dx = diff(f,x)
df_dy = diff(f,y)
% f的二阶偏导数
d2f_dx2 = diff(f,x,x)
d2f_dy2 = diff(f,y,y)
d2f_dxdy = diff(f,x,y)
```

例：已知 $ f(x) = \frac{e^{x^2}}{x^3-x+3} $, 求 $ \frac{df}{dx} $

```matlab
syms x
f = exp(x^2)/(x^3-x+3);
df_dx = diff(f,x)
```

例：已知 $ f(x) = \frac{x^2+xy-1}{y^3+x+3} $, 求 $ \frac{df}{dx} \, \frac{df}{dy} $

```matlab
syms x y
f = (x^2+x*y-1)/(y^3+x+3);
df_dx = diff(f,x)
df_dy = diff(f,y)
```

### 求积分表达式

使用函数：

+ symbolic function使用的积分函数 `int()`
+ 将一个symbolic function中的sym进行替换 `subs()`

求 $ z = \int y dx = \int x^2 e^x dx \,, \, z(0)=0 $

```matlab
syms x
y = x^2*exp(x);
z = int(y) % 求得不定积分
z = z - subs(z, x, 0) % 使满足初值条件，subs为将0代入z中的x
```

## 数值根 Numeric Root Finding Approach

### 解方程

`fsolve()`

`fzero()` 功能和使用同`fsolve()` 但只能得到图像穿过x轴的解

`root()` 只能解多项式方程

```matlab
f = @(x)(1.2*x+0.3+x*sin(x));
fsolve(f, 0) % f为function handle, 0为initial guess
fzero(f,0) % f为function handle, 0为initial guess
```

```matlab
f = @(x)(1.2*x+0.3+x*sin(x));
options = optimset('MaxIter',1e3,'TolFun',1e-10); % 指定最大迭代次数和精度
fsolve(f, 0, options) % f为function handle, 0为initial guess
fzero(f,0, options) % f为function handle, 0为initial guess
```

例：解 $ f(x) = x^3 - 6x^2-12x+81 $

```matlab
f = [1 -6 -12 81];
x = roots(f) % 可得到复数解
```

### 解方程组

例：解 $ f(x,y) = \begin{cases} 2x-y-e^{-x} \\ -x+2y-e^{-y}  \end{cases} \,\,\,\,\, (x,y)=(-5,-5) $

```matlab
initial_x = [-5 -5];
fsolve(@func,initial_x)

function F = func(x)
	F(1) = 2*x(1)-x(2)-exp(-x(1));
	F(2) = -x(1)+2*x(2)-exp(-x(2));
end 
```

