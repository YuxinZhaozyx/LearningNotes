# 微分与积分

## 多项式微分

$$
f(x) = 5x^4 -2x^2 +1
$$

在 MATLAB 中表示为`p = [5 0 -2 0 1]`

微分后为
$$
f'(x) = 20x^3 -4x
$$
表示为 `dp = [20 0 -4 0]`

使用函数：

+ 计算微分后的多项式 `polyder()`

+ 计算x为某个值时多项式的值 `polyval()`

```matlab
p = [5 0 -2 0 1];
dp = polyder(p);
x = -10:0.1:10;
y_p = polyval(p,x);
y_dp = polyval(dp,x);
plot(x,y_p, x,y_dp);
legend('f(x)','f''(x)');
```
## 多项式积分

$$
f(x) = 5x^4 -3x^2 +1
$$

积分后为
$$
\int_0^x f(x)\,dx = x^5 -x^3 +x+ C \\其中, C为常数
$$
使用函数：

+ 计算积分后的多项式 `ployint()`

```matlab
p = [5 0 -2 0 1];
sp = polyint(p, 3); % 常数C = 3
x = -10:0.1:10;
y_p = polyval(p,x);
y_sp = polyval(sp,x);
plot(x,y_p, x,y_sp);
legend({'f(x)','$ \int_0^x f(x)\,dx $'},'Interpreter','latex');
```

## 数值微分

$$
f'(x) = \lim_{h \to 0}\frac{f(x_0+h)-f(x_0)}{h}
$$

使用函数：

+ `diff()` 将向量相邻元素求差后返回向量

例：(Given  $ f(x)=sin(x) $ find $ f'(x_0) $ at $ x_0 = \pi/2 $ using h = 0.1)

```matlab
x0 = pi/2;
h = 0.1;
x = [x0 x0+h];
y = sin(x);
m = diff(y)./diff(x)
```
```matlab
f = @(x)(exp(-x).*sin((x.^2)./2));
hold on
h=0.1;
x=0:h:2*pi;
m=diff(f(x))./diff(x);
plot(x(1:end-1),m);
h=0.01;
x=0:h:2*pi;
m=diff(f(x))./diff(x);
plot(x(1:end-1),m);
h=0.001;
x=0:h:2*pi;
m=diff(f(x))./diff(x);
plot(x(1:end-1),m);
hold off
legend('h=0.1','h=0.01','h=0.001');
```

## 数值积分

$$
A = \int_0^2 4x^3\,dx
$$

使用函数：

+ `sum()` 求和 (Midpoint Rule)
+ `trapz()`  梯形数值积分 (Trapezoid Rule梯形法)

```matlab
% Midpoint Rule 矩形面积求和
h = 0.05;
x = 0:h:2;
midpoint = (x(1:end-1)+x(2:end))./2;
y = 4*midpoint.^3;
s = sum(h*y)
```

```matlab
% Trapezoid Rue 梯形法
h = 0.05;
x = 0:h:2;
y = 4*x.^3;
s = trapz(h,y); % 等同于 s = h*trapz(y)
```

```matlab
% Second-order Rule (one thirds Simpson's Rule)
h = 0.05;
x = 0:h:2;
y = 4*x.^3;
s = h/3*(y(1)+2*sum(y(3:2:end-2))+4*sum(y(2:2:end))+y(end))
```

Rule | Degree | Formula
--- | --- | --- 
Midpoint Rule | 0 | $ \int_a^b f(x)dx = 2h\sum_{i=0}^{\frac{n}{2}-1}f(x_{2i+1}) $ 
Trapezoid Rule | 1 | $ \int_a^b f(x)dx = \frac{h}{2}(f(a)+2\sum_{i=1}^{n-1}f(x_i)+f(b)) $ 
Simpson's Rule | 2 | $ \int_a^b f(x)dx = \frac{h}{3}(f(a)+2\sum_{i=1}^{\frac{n}{2}-1}f(x_{2i})+4 \sum_{i=2}^{\frac{n}{2}}f(x_{2i-1}) +f(b))$ 

### 内建函数 integral()

普通积分`integral()`

二重积分`integral2()`

三重积分`integral3()`

例：$ \int_0^2\frac{1}{x^3-2x-5}dx $

```matlab
f = @(x) 1./(x.^3-2*x-5);
m = integral(f,0,2)
```

例：$ \int_0^\pi \int_\pi^{2\pi}(y \cdot sin(x) +x \cdot cos(y))\,dxdy $

```matlab
f = @(x,y) y.*sin(x)+x.*cos(y);
m = integral2(f,pi,2*pi,0,pi)
```

例：$ \int_{-1}^1 \int_0^1 \int_0^\pi (y \cdot sin(x) +z \cdot cos(y))\,dxdydz $

```matlab
f = @(x,y,z) y.*sin(x)+z.*cos(y);
m = integral3(f,0,pi,0,1,-1,1)
```



