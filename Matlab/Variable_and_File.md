# 变量与档案存取

## Variable (Data) Type Conversion

- double ()
- single()
- int8()
- int16()
- int32()
- int64()
- uint8()
- uint16()
- uint32()
- uint64()

## Char & String

### Char

`'a'`

### String

`str = 'string'`

#### String 的比较运算符

```matlab
str = 'aardvark';
'a' == str; %逐个比较str中每个元素是否为a，得到1和0的向量
str(str=='a')='z'; %将str中的a替换为z
```

## Structure

```matlab
student.name = 'Ann Lane';
student.id = '1122';
student.grade = [95 100 90; 95 82 97];

student % 只有一个student情况下，student为实例

%扩充student办法
student(2).name = 'Job Li';
student(2).id = '2334';
student(2).grade = [80 45 98; 60 70 80];

student(1) % 此时student(1),student(2)为实例
student(2) 
```

保存结构的Array称之为field。

Structure Function | illustration 
--- | ---
cell2struct | Convert cell array to structure array
fieldnames | Field names of structure, or public fields of object
getfield | Field of structure array
isfield | Determine whether input is structure array field
isstruct | Determine whether input is structure array
orderfields | Order fields of structure array
rmfield | Remove fields from structure
setfield | Assign values to sturcture array field
struct | Create structure array
struct2cell | Convert structure to cell array
structfun | Apply function to each field of scalar structure

### Nesting Structures

```matlab
A = struct('data',[3 4 7; 8 0 1], ...
		  'nest', struct('testnum','Test 1', ...
						'xdata', [4 2 8], ...
						'ydata', [7 1 6]));
A(2).data = [9 3 2; 7 6 5];
A(2).nest.testnum = 'Test 2';
A(2).nest.xdata = [3 4 2];
A(2).nest.ydata = [5 0 9];
```

## Cell Array

用 `{}` 声明

方式1：

```matlab
A(1,1) = {[1 4 3; 0 5 8; 7 2 9]};
A(1,2) = {'Anne Smith'};
A(2,1) = {3+7i};
A(2,2) = {-pi:pi:pi};
A
```

方式2：

```matlab
A{1,1} = [1 4 3; 0 5 8; 7 2 9];
A{1,2} = 'Anne Smith';
A{2,1} = 3+7i;
A{2,2} = -pi:pi:pi;
A
```

Cell Array Functions | illustration
--- | ---
cell | Create cell array
cell2mat | Convert cell array to numeric array
cell2struct | Convert cell array to structure array
celldisp | Cell array contents
cellfun | Apply function to each cell in cell array
cellplot | Graphically display structure of cell array
cellstr | Create cell array of strings from character array
iscell | Determine whether input is cell array
mat2cell | Convert array to cell array with different sized cells
num2cell | Convert array to cell array with consistently sized cells
struct2cell | Convert structure to cell array 

## Multidimensional Array

方法1：

```matlab
A{1,1,1} = [1 2; 4 5];
A{1,2,1} = 'name';
A{2,1,1} = 2-4i;
A{2,2,1} = 4;
A{1,1,2} = 'any';
A{1,2,2} = 3;
A{2,1,2} = 4;
A{2,2,2} = [4 3];
```

方法2：

```matlab
A = [1 2; 3 4];
B = [5 6; 7 8];
C = cat(1,A,B); %第一维度拼接 C=[1 2; 3 4; 5 6; 7 8]
C = cat(2,A,B); %第二维度拼接 C=[1 2 5 6; 3 4 7 8]
C = cat(3,A,B); %第三维度拼接 C有两个layer
```



## File

将当前workspace的所有数据存储于mat文件

```matlab
clear;
a = magic(4);
save mydata1.mat
save mydata2.mat -ascii
```

从mat文件读取数据

```matlab
load('mydata1.mat')
load('mydata2.mat','-ascii');
```

将当前workspace的所有数据保存于xlsx文件

```matlab
M = mean(Score')';
xlswrite('04Score.xlsx', M, 1, 'E2:E4');
xlswrite('04Score.xlsx',{'Mean'},1,'E1');
Score = xlsread('04Score.xlsx')
Score = xlsread('04Score.xlsx', 'B2:D4') % 只读取B2:D4的部分
[Score Header] = xlsread('04Score.xlsx') % 数值部分存在Score，文字部分存在Header
```

### Low-level File I/O Functions

Function | Description
--- | ---
fopen | Open file, or obtain information about open files
fclose | Close one or all open files
fscanf | Read data from text file
fprintf | Write data to text file
feof | Test for end-of-file

```matlab
fid = fopen('filename','permission');
status = fclose(fid);
```

```matlab
x  = 0:pi/10:pi;
y = sin(x);
fid = fopen('sinx.txt','w');
for i = 1: 11
	fprintf(fid, '%5.3f %8.4f\n', x(i), y(i));
end
fclose(fid);
type sinx.txt
```

```matlab
fid = fopen('asciiData.txt','r');
i = 1;
while ~feof(fid)
	name(i,:) = fscanf(fid,'%5c',1);
	year(i) = fscanf(fid, '%d',1);
	no1(i) = fscanf(fid,'%d',1);
	no2(i) = fscanf(fid,'%d\n',1);
	i = i+1;
end
fclose(fid);
```



