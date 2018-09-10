# 图像分析

## 读取与显示图像

读取图像：`imread()`

显示图像：`imshow()`

```matlab
clear
close all
I = imread('pout.tif'); % read
imshow(I) % show
```

## 获取图像信息

use `imageinfo('<imagename>')`

## 查看图像的工具

use `imtool('<imagename>')`

## 操作图像像素

若`I` 为图像矩阵

`I(row,column)` `I(row, column, layer)`

## 图像算术运算

Function | illustration
--- | ---
imabsdiff | Absolute difference of two images
imadd | Add two images or add constant to image
imapplymatrix | Linear combination of color channels
imcomplement | Complement image
imdivide | Divide one image into another or divide image by constant
imlincomb | Linear combination of images
immultiply | Multiply two images or multiply image by constant
imsubtract | Subtract one image from another or subtract constant from image

例：

```matlab
I = imread('rice.png');
subplot(1,2,1); imshow(I);
J = immultiply(I,1.5);
subplot(1,2,2); imshow(J);
```

```matlab
I = imread('rice.png');
J = imread('cameraman.tif');
K = imadd(I,J);
subplot(1,3,1); imshow(I);
subplot(1,3,2); imshow(K);
subplot(1,3,3); imshow(J);
```

## 直方图 Histogram

显示直方图：`imhist()`

直方图均衡化：`histeq()`

 例：

```matlab
I1 = imread('pout.tif');
I2 = histeq(I1);
subplot(1,4,1); imhist(I1);
subplot(1,4,2); imshow(I1);
subplot(1,4,3); imhist(I2);
subplot(1,4,4); imshow(I2);
```

## 几何变换

### 图像旋转

`imrotate`

```matlab
I = imread('rice.png');
subplot(1,2,1);
imshow(I);
J = imrotate(I, 35, 'bilinear');
subplot(1,2,2);
imshow(J);
size(I)
size(J)
```

### 图像缩放

`imresize()`

```matlab
I = imread('rice.png');
J = imresize(I, 0.5);
```

## 保存图像

`imwrite()`

支持格式：`bmp` `gif` `hdf` `jpg` `jpeg` `jp2` `jpx` `pcx` `pnm` `ppm` `ras` `tif` `tiff` `xwd`

例：`imwrite(I, 'pout2.png');`

## 图像二值化

`graythresh()` 计算最佳二值化阈值

`im2bw()` 将一张图像转换为二值图像

```matlab
I = imread('rice.png');
level = graythresh(I);
bw = im2bw(I,level);
subplot(1,2,1);
imshow(I);
subplot(1,2,2);
imshow(bw);
```

### 背景估计

Estimation for the gray level of the background

```matlab
I = imread('rice.png');
BG = imopen(I,strel('disk',15));
imshow(BG);
```

### 背景差分

``` matlab
I = imread('rice.png');
subplot(1,3,1);
imshow(I);
BG = imopen(I, strel('disk',15));
subplot(1,3,2);
imshow(BG);
I2 = imsubtract(I, BG);
subplot(1,3,3);
imshow(I2);
```

## 连通域标记

`bwlabel()` 用于二值图像

```matlab
I = imread('rice.png');
BG = imopen(I, strel('disk',15));
I2 = imsubtract(I, BG);
level = graythresh(I2);
BW = im2bw(I2, level);
[labeled, numObjects] = bwlabel(BW, 8); % labeled为标记后图像
```

`label2rgb()` 将标记好的图像用色彩显示

```matlab
RGB_label = label2rgb(labeled);
imshow(RGB_label);
```

## 对象属性: regionprops()

`regionprops()` 提供每个连通域的属性的集合

```matlab
I = imread('rice.png');
BG = imopen(I, strel('disk',15));
I2 = imsubtract(I, BG);
level = graythresh(I2);
BW = im2bw(I2, level);
[labeled, numObjects] = bwlabel(BW, 8); % labeled为标记后图像
graindata = regionprops(labeled, 'basic');
graindata(51) % 第51颗米
```

## 交互式选择

`bwselect()` 用于二值图像，返回选择的点的连通区域的图像

```matlab
I = imread('rice.png');
level = graythresh(I);
BG = imopen(I, strel('disk',15));
I2 = imsubtract(I, BG);
BW = im2bw(I2, graythresh(I2));
ObjI = bwselect(BW);
imshow(ObjI);
```



