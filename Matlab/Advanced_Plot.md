# 进阶绘图

## Special Plots

Function | Description
--- | ---
`loglog` | Graph with logarithmic scales for both axes
`semilogx` | Graph with a logarithmic scale for the x-axis and a linear scale for the y-axis
`semilogy` | Graph with a logarithmic scale for the y-axis and a linear scale for the x-axis
`plotyy` | Graph with y-tick labels on the left and right side
`hist` | Histogram plot
`bar` | Bar graph
`pie` | Pie chart
`polar` | Polar coordinate plot
`stairs` | Stairs chart
`stem` | Stem chart
`boxplot` | Boxplot
`errorbar` | Error bar
`fill` | Fill graph
`imagesc` | Visualizing data as an image

### Logarithm Plots

``` matlab
x = logspace(-1,1,100); % 在[10^-1,10^1]内取100个值
y = x.^2
subplot(2,2,1);
plot(x,y);
title('Plot');
subplot(2,2,2);
semilogx(x,y); % x轴取对数
title('Semilogx');
subplot(2,2,3);
semilogy(x,y); % y轴取对数
title('Semilogy');
subplot(2,2,4);
loglog(x,y); % x,y轴都取对数
title('Loglog');
```

### plotyy()

```matlab
x = 0:0.01:20;
y1 = 200*exp(-0.05*x).*sin(x);
y2 = 0.8*exp(-0.5*x).*sin(10*x);
[AX,H1,H2] = plotyy(x,y1,x,y2); % AX为坐标轴handle， H1、H2分别为两条曲线的handle
set(get(AX(1),'Ylabel'), 'String', 'Left Y-axis'); % 将左边坐标轴的Label改为'Left Y-axis'
set(get(AX(2),'Ylabel'), 'String', 'Right Y-axis'); % 将右边坐标轴的Label改为'Right Y-axis'
title('Labeling plotyy');
set(H1,'LineStyle','--');
set(H2,'LineStyle',':');
```

### Histogram

```matlab
y = randn(1,1000);
subplot(2,1,1);
hist(y,10); % 10个柱
title('Bins = 10');
subplot(2,1,2);
hist(y,50); % 50个柱
title('Bins = 50');
```

### Bar Chart

```matlab
x = [1 2 5 4 8];
y = [1 2 3 4 5];
z = [x,y];
subplot(1,3,1); bar(x); title('A bargraph of vector x');
subplot(1,3,2); bar(z); title('A bargraph of vector z');
subplot(1,3,3); bar3(z); title('A 3D bargraph');
```

#### Stacked and Horizontal Bar Charts

```matlab
x = [1 2 5 4 8];
y = [1 2 3 4 5];
z = [x y];
subplot(1,2,1);
bar(z,'stacked'); % Stacked Bar chart (not works)
title('Stacked');
subplot(1,2,2);
barh(z,'stacked'); % Horizontal Bar Chart
title('Horizontal');
```

### Pie Charts

```matlab
a = [10 5 20 30];
subplot(1,3,1); pie(a);
subplot(1,3,2); pie(a,[0,0,0,1]); % 1表示将该处扇形于其他扇形分开
subplot(1,3,3); pie3(a,[0,0,0,1]); % 3D pie chart
```

### Polar Chart

```matlab
x = 1:100; theta = x/10; r = log10(x);
subplot(1,4,1); polar(theta, r);

theta = linspace(0, 2*pi); r = cos(4*theta);
subplot(1,4,2); polar(theta, r);

theta = linspace(0,2*pi,6); r = ones(1, length(theta));
subplot(1,4,3); polar(theta, r);

theta = linspace(0,2*pi); r = 1-sin(theta);
subplot(1,4,4); polar(theta, r);
```

### Stairs and Stem Charts

```matlab
x = linspace(0, 4*pi, 40);
y = sin(x);
subplot(1,2,1); stairs(y);
subplot(1,2,2); stem(y);
```

### Boxplot and Error Bar

```matlab
load carsmall
boxplot(MPG, Origin);
```

```matlab
x = 0:pi/10:pi;
y = sin(x);
e = std(y)*ones(size(x));
errorbar(x,y,e);
```

### fill()

```matlab
t = (1:2:15)'*pi/8;
x = cos(t);
y = sin(t);
fill(x,y,'r'); % 'r'表示填充为红色
axis square off;
text(0,0,'STOP','Color','w','FontSize',80, 'FontWeight','bold','HorizontalAlignment','center');
```

### Visualizing Data as an Image: imagesc()

```matlab
[x,y] = meshgrid(-3:0.2:3, -3:0.2:3);
z = x.^2+x.*y +y.^2;
surf(x,y,z); % 3D graph 
box on;
set(gca, 'FontSize', 16);
zlabel('z');
xlim([-4 4]); xlabel('x');
ylim([-4 4]); ylabel('y');
```

```matlab
imagesc(z); axis square; xlabel('x'); ylabel('y');
colorbar; % 显示各颜色对应的值的参考图
```

#### Colormap

Syntax: `colormap([Name])` 

`[Name]` 的选择有 `parula` `jet` `hsv` `hot` `cool` `spring` `summer` `autumn` `winter` `gray` `bone` `copper` `pink` `lines` `colorcube` `prism` 

用处：跟在上例`imagesc()`后可改变图像对应的颜色

A color map is a matrix of 256*3 [r g b; ...]

`a = colormap(prism)`

自定义Color map

```matlab
a = ones(256,3);
colormap(a);
```

## 3D 绘图

Function | Description
--- | ---
plot3 | 3D line plot
surf | 3D shaded surface plot
surfc | Contour plot under a 3D shaded surface plot
surface | Create surface object
meshc | Plot a contour graph under mesh graph
contour | Contour plot of matrix
contourf | Filled 2D contour plot

### plot3()

```matlab
z = 0:pi/50:10*pi;
x = cos(z);
y = sin(z);
plot3(x,y,z);
grid on;
axis square;
```

### meshgrid() & mesh() & surf()

```matlab
x = -2:1:2;
y = -2:1:2;
[X,Y] = meshgrid(x,y);
```

$$
x = \left[ \begin{matrix} -2 &  -1 & 0 & 1 & 2\end{matrix} \right]
$$

$$
y = \left[ \begin{matrix} -2 &  -1 & 0 & 1 & 2\end{matrix} \right]
$$

$$
X = \begin{bmatrix} 
	-2 & -1 & 0 & 1 & 2 \\
	-2 & -1 & 0 & 1 & 2 \\
	-2 & -1 & 0 & 1 & 2 \\
	-2 & -1 & 0 & 1 & 2 \\
	-2 & -1 & 0 & 1 & 2 
\end{bmatrix}
$$

$$
Y = \begin{bmatrix} 
	-2 & -2& -2& -2& -2 \\
	-1 & -1 & -1 & -1 & -1 \\
	0 &0 & 0 & 0&0 \\
	-1 & -1 & -1 & -1 & -1 \\
	-2 & -2& -2& -2& -2 
\end{bmatrix}
$$

```matlab
x = -3.5:0.2:3.5;
y = -3.5:0.2:3.5;
[X Y] = meshgrid(x,y);
Z = X.*exp(-X.^2-Y.^2);
subplot(1,2,1); mesh(X,Y,Z); % 只有网格没有绘制表面
subplot(1,2,2); surf(X,Y,Z); % 绘制了表面
```

### contour() 等高线

```matlab
x = -3.5:0.2:3.5;
y = -3.5:0.2:3.5;
[X Y] = meshgrid(x,y);
Z = X.*exp(-X.^2-Y.^2);
contour(X,Y,Z);
axis square;
colorbar;
```

```matlab
x = -3.5:0.2:3.5;
y = -3.5:0.2:3.5;
[X Y] = meshgrid(x,y);
Z = X.*exp(-X.^2-Y.^2);
subplot(1,3,1);
contour(Z,[-0.45:0.05:0.45]); % 画出指定Z轴高度的等高线
axis square;
subplot(1,3,2);
[C,h] = contour(Z); 
clabel(C,h); % 将等高线的数值标记在线上
axis square;
subplot(1,3,3);
contourf(Z); % 使用填充的等高线
axis square;
```

### meshc() & surfc()

在mesh和surf的结果下方画上等高线

```matlab
x = -3.5:0.2:3.5;
y = -3.5:0.2:3.5;
[X Y] = meshgrid(x,y);
Z = X.*exp(-X.^2-Y.^2);
subplot(1,2,1); meshc(X,Y,Z);
subplot(1,2,2); surfc(X,Y,Z);
```

### View Angle: view()

syntax: `view(azimuth, elevation)` azimuth为方位角(角度制)，elevation为仰角(角度制)。

```matlab
sphere(50);
shading flat;
light('Position',[1 3 2]);
light('Position',[-3 -1 3]);
material shiny;
axis vis3d off;
set(gcf, 'Color', [1 1 1]);
view(-45,20);
```

### light()

``` matlab
[X Y Z] = sphere(64);
h = surf(X,Y,Z);
axis square vis3d off;
reds = zeros(256,3);
reds(:,1) = ((0:256.-1)/255)';
colormap(reds);
shading interp;
lighting phong;
set(h, 'AmbientStrength', 0.75, 'DiffuseStrength',0.5);
L = light('Position',[-1 -1 -1]); % L为光源的handle
set(L,'Position',[-1 -1 0]); % 再次调用light()会生成新的光源，要修改旧光源使用光源的handle
set(L,'Color','g'); % 修改光源的颜色
```

### patch()

画多面体

```matlab
v = [0 0 0; 1 0 0; 1 1 0; 0 1 0; ...
	0.25 0.25 1; 0.75 0.25 1; 0.75 0.75 1;0.25 0.75 1]; % 顶点
f = [1 2 3 4; 5 6 7 8; 1 2 6 5; 2 3 7 6; 3 4 8 7; 4 1 5 8]; % 指定哪些顶点构成一个面
subplot(1,2,1);
patch('Vertices',v,'Faces',f,'FaceVertexCData',hsv(6),'FaceColor','flat');
view(3); axis square tight; grid on;
subplot(1,2,2);
patch('Vertices',v,'Faces',f,'FaceVertexCData',hsv(8),'FaceColor','interp');
view(3); axis square tight; grid on;
```

