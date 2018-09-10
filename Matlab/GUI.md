# 图像界面GUI

## Starting A GUI Program

Type `guide` （graphical user interface design environment)  in command window to create a MATLAB GUI interactively.

## `handles` - Parents of the GUI Objects

若figure中有多个组件时，可用 `handles` 获得对应组件对象的handle. 如 `handles.axes1` `handles.axes2` `handles.pushbutton1` `handles.pushbutton2` .

例：(指定axes进行画图)

```matlab
handles.peaks = peaks(35);
handles.membrane = membrane;
[x y] = meshgrid(-8:0.5:8);
r = sqrt(x.^2+y.^2) + eps;
sinc = sin(r)./r;
handles.sinc = sinc;
handles.current_data = handles.peaks;
% 方法1
surf(handles.axes1, handles.current_data);
% 方法2
axes(handles.axes1);
surf(handles.current_data);
```

### Using `handles` to Store Variables

```matlab
% 将数据储存到handles中
handles.myData = a;
guidata(hObject, handles);
% 从handles中读取数据
a = handles.myData;
```



## set() & get()

```matlab
a = get(handles.slider1, 'Value');
set(handles.text1, 'String', num2str(a));
```

## Compiling the GUI Program

use command `deploytool	`

