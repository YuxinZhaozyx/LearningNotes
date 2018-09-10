# 回归与内插

## 简单线性回归

Define sum of squared error (SSE):
$$
SSE = \sum_i \epsilon^2 = \sum_i (y_i- \hat{y_i})^2
$$
Given that the regression model: $ \hat{y_i} = \beta_0 + \beta_1 x_i $
$$
SSE = \sum_i (y_i-\beta_0 - \beta_1 x_i)^2
$$
Minimize the SSE



`ployfit()` 用多项式曲线进行拟合

```matlab
x = [-1, 2 -0.5 0.3 0.9 1.8 2.6 3 3.5];
y = [-15 6 -8.5 2.2 4.5 6.6 8.2 8.9 10.0];
n = 1; % 多项式的最高次
fit = polyfit(x,y,n); 
xfit = x(1):0.1:x(end);
yfit = polyval(fit,xfit);
plot(x,y,'ro',xfit,yfit);
legend('data points','best-fit');
```

###  线性相关系数

`corrcoef()`

```matlab
x = [-1, 2 -0.5 0.3 0.9 1.8 2.6 3 3.5];
y = [-15 6 -8.5 2.2 4.5 6.6 8.2 8.9 10.0];
corrcoef(x,y) 
% 返回一个矩阵 [x-x x-y; y-x y-y] 不同位置表示不同变量之间的线性相关系数
```

 ### 多变量线性回归

`regress()`

```matlab
% y = a + bx1 +cx2
load carsmall;
y = MPG;
x1 = Weight;
x2 = Horsepower;
X = [ones(length(x1),1) x1 x2]; % 每一列为不同的变量
b = regress(y,X);
x1fit = min(x1):100:max(x1);
x2fit = min(x2):10:max(x2);
[X1Fit X2Fit] = meshgrid(x1fit,x2fit);
YFit = b(1)+b(2)*X1Fit+b(3)*X2Fit;
scatter3(x1,x2,y,'filled');
hold on;
mesh(X1Fit,X2Fit,YFit);
hold off;
xlabel('Weight');
ylabel('Horsepower');
zlabel('MPG');
view(50,10);
```

## 非线性拟合

### Curve Fitting Toolbox

`cftool`

## 内插

Function | illustration
--- | ---
interp1() | 1-D data interpolation 
interp2() | 2-D data interpolation
pchip() | Piecewise Cubic Hermite Interpolation Polynomial
spline() | Cublic spine data interpolation
mkpp() | Make piecewise polynomial

```matlab
x = linspace(0,2*pi,40);
x_m = x;
x_m([11:13, 28:30]) = NaN; % 除去之中的一些片段
y_m = sin(x_m);
plot(x_m,y_m,'ro','MarkerFaceColor','r');
xlim([0,2*pi]);
ylim([-1.2,1.2]);
box on;
set(gca, 'XTick',0:pi/2:2*pi);
set(gca, 'XTickLabel',{'0','p/2','p','3p/2','2p'});

% 线性内插
m_i = ~isnan(x_m);
y_i = interp1(x_m(m_i),y_m(m_i),x);
hold on;
plot(x,y_i,'-b','LineWidth',2);
hold off;

% 平滑内插
m_i = ~isnan(x_m);
y_i = spline(x_m(m_i),y_m(m_i),x);
hold on;
plot(x,y_i,'-g','LineWidth',2);
hold off;
```

`spline()` 和 `pchip()` 同为平滑内插，但`pchip()` 在坡度急剧变换恢复直线的地方，直线部分不会像`spline()` 出现变化

```matlab
x = -3:1:3;
y = [-1 -1 -1 0 1 1 1];
t = -3:0.01:3;
s = spline(x,y,t);
p = pchip(x,y,t);
hold on;
plot(t,s,':g', 'LineWidth',2);
plot(t,p,'--b', 'LineWidth',2);
scatter(x,y,'MarkerFaceColor','r');
hold off;
box on;
legend('Cublc Spline','Hermite Polynomial');
```

## 2D interpolation

`interp2()`

```matlab
xx = -2:0.5:2;
yy = -2:0.5:3;
[X Y] = meshgrid(xx,yy);
Z = X.*exp(-X.^2-Y.^2);
surf(X,Y,Z,'Marker','o','MarkerFaceColor','r');

% 线性内插
xx_i = -2:0.1:2;
yy_i = -2:0.1:3;
[X_i Y_i] = meshgrid(xx_i,yy_i);
Z_i = interp2(xx,yy,Z,X_i,Y_i);
surf(X_i,Y_i,Z_i);

% 平滑内插
xx_i = -2:0.1:2;
yy_i = -2:0.1:3;
[X_i Y_i] = meshgrid(xx_i,yy_i);
Z_i = interp2(xx,yy,Z,X_i,Y_i,'cubic');
surf(X_i,Y_i,Z_i);
```



