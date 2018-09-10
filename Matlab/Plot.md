# 基本绘图

## plot()

`plot(x,y)` plots each vector pairs (x,y)

`plot(y)` plots each vector paris (x,y), where x=[1...n], n=length(y)

每次画图后默认会清空，若需要保留，使用`hold`

```matlab
hold on
plot(cos(0:pi/20:2*pi));
plot(sin(0:pi/20:2*pi));
hold off
```

### Plot Style

`plot(x,y,'str')` plots each vector pairs (x,y) using the format defined in str (check LineSpec).

Data markers | Line types | Colors
--- | --- | ---
Dot(.) | Solid line(-) | Black(k)
Asterisk(\*) | Dashed line(--) | Blue(b)
Cross(X) | Dash-dotted line(-.) | Cyan(c)
Circle(o) | Dotted line(:) | Green(g)
Plus sign(+) | | Magenta(m)
Square(s) | | Red(r)
Diamond(d) | | White(w)
Five-pointed star(p) | | Yellow(y)
Down triangle(v) | |
Up triangle(^) | |
Left triangle(<) | |
Right triangle(>) | |
hexagram(H) | |

```matlab
x = 0:0.5:4*pi;
y = sin(x);
h = cos(x);
w = 1./(1+exp(-x));
g = (1/(2*pi*2)^0.5).*exp((-1.*(x-2*pi).^2)./(2*2^2));
plot(x,y,'bd-', x,h,'gp:', x,w,'ro-', x,g,'c^-'); % 绘图
legend('sin(x)','cos(x)','sigmoid', 'gauss'); % 图示
title('Function Plots'); % 标题
xlabel('x = 0 to 4\pi'); % 坐标轴名称,其中数学公式使用LaTex
ylabel('y = e^{-x}');
```

```matlab
x = linspace(0,3);
y = x.^2.*sin(x);
plot(x,y);
line([2,2],[0,2^2*sin(2)]); % 画直线
str = '$$ \int_{0}^{2} x^2\sin(x) dx $$'; % LaTex
text(0.25,2.5,str,'Interpreter','latex'); % 在图上添加文本，使用LaTex解释
annotation('arrow','X',[0.32,0.5],'Y',[0.6,0.4]); % 画箭头，(0.32,0.6)和(0.5,0.4)假定图形坐标为1:1
```

```matlab
t = 1:0.05:2;
f = @(t)(t.^2);
g = @(t)sin(2*pi.*t);
plot(t,f(t),'k-',t,g(t),'or');
legend('f=t^2','g=sin(2\pit)');
title('Mini Assignment');
xlabel('Time(t)');
ylabel('f(t),g(t)');
```

### 修改绘图的属性

`hLine = plot(x,y)` 获得绘制出的曲线的handle

```matlab
x = linspace(0,2*pi,1000);
y = sin(x);
h = plot(x,y);
get(h) % 获得绘制出的曲线的object信息
get(gca) % 获得坐标轴的object信息
set(gca,'XLim', [0, 2*pi]); % 修改x轴长度
set(gca,'YLim', [-1.2, 1.2]); % 修改y轴长度
set(gca,'FontSize',25); % 修改坐标轴数字大小
set(gca,'XTick', 0:pi/2:2*pi); % 修改坐标轴数值间隔
set(gca,'FontName','Helvetica'); % 坐标轴字体
set(gca,'XTickLabel',{'0','p/2','p','3p/2','2p'}); % 以文本形式设置数值间隔显示的字符串(p显示为π)
set(h,'LineStyle','-.','LineWidth',7.0,'Color','g'); % 设置线型、线宽、颜色
```

```matlab
x = rand(20,1);
set(gca, 'FontSize', 18);
plot(x, '-md','LineWidth',2,'MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
xlim([1,20]); % 相当于set(gca,'XLim',[1,20])
```

Utility function | Purpose
--- | ---
gca | Return the handle of the 'current' axes
gcf | Return the handle of the 'current' figure
allchild | Find all children of specified objects
ancestor | Find ancestor of graphics object
delete | Delete an object
findall | Find all graphics objects

## 多图像

使用 `figure` 创建新绘图窗口

```matlab
x = -10:0.1:10;
y1 = x.^2 - 8;
y2 = exp(x);
figure, plot(x,y1); % y1将出现在figure1窗口
figure, plot(x,y2); % y2将出现在figure2窗口
```

`figure('Position',[left,bottom,width,height])` 设置新绘图窗口位置和大小

### Several Plots in One Figure

`subplot(m,n,index)`

将一个figure分为`m`行`n`列个小窗口用于在一副图上绘制多个图，`index` 为图的索引(按行排列如[1 2 3; 4 5 6])。

```matlab
t = 0:0.1:2*pi; 
x = 3*cos(t);
y = sin(t);
subplot(2,2,1); plot(x,y); axis normal
subplot(2,2,2); plot(x,y); axis square
subplot(2,2,3); plot(x,y); axis equal
subplot(2,2,4); plot(x,y); axis equal tight
```

### Control of Grid, Box and Axis

command | illustration
--- | ---
grid on/off | Make the grid visible or invisible
box on/off | Make the box visible or invisible
axis on/off | Make the axes visible or invisible
axis normal | Automatically adjust the aspect ratio of the axes and the relative scaling of the data units
axis square | Make the current axes region square
axis equal | Set the aspect ratio so that the data units are the same in every deirection
axis equal tight | Set the axis limits to the range of the data
axis image | Let the plot box fits tightly around the data
axis ij | Place the origin of the coordinate system in the upper left corner
axis xy | Place the origin of the lower left corner

## Saving Figures into Files

`saveas(gcf, '<filename>', '<formattype>');`

例：` saveas(gcf, '0.jpeg', 'jpeg');`

To control size and resolution, use `print` instead.

Option | Bitmap Image Format
--- | ---
`'jpeg'` | JPEG 24-bit
`'png'` | PNG 24-bit
`'Liff'` | TIFF 24-bit (compressed)
`'bmpmono'` | BMP Monochrome
`'bmp'` | BMP 24-bit
`'bmp256'` | BMP 8-bit (256 color, uses a fixed color map) 

Option | Vector Graphics Format
--- | ---
`'pdf'` | Full page Portable Document (PDF) color
`'eps'` | Encapusulated PostScript (EPS) Level 3 black and white
`'cpsc'` | Encapusulated PostScript (EPS) Level 3 color
`'meta'` | Enhanced Metafile (Windows only)
`'svg'` | SVG (scalable vector graphics)
`'ps'` | Full-page PostScript (PS) Level 3 black and white
`'psc'` | Full-page PostScript (PS) Level 3 color



