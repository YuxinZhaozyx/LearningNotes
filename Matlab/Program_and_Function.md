# 结构化程序与自定义函数

`%` 为注释符

## 逻辑运算符

Operator | illustration
--- | ---
`<` | less than
`<=` | less than or equal to
`>` | greater than
`>=` | greater than or equal to
`==` | equal to
`~=` | not equal to
`&&` | and
`||` | or

## 指令

### if elseif else

```matlab
if condition1
	statement1
elseif condition2
	statement2
else
	statement3
end
```

### switch

```matlab
switch expression
case value1
	statement1
case value2
	statement2
otherwise
	statement
end
```

### while

```matlab
while expression
	statement
end
```

### for

```matlab
for variable = start: increment: end
	commands
end
```

例：

```matlab
for n=1:10
	a(n)=2^n
end
disp(a)
```

## 自定义函数

例1：

$$
x = x_0 + v_0t + \frac 12gt^2
$$

```matlab
function x = freebody(x0,v0,t)

x = x0 + v0.*t + 1/2*9.8*t.*t
```

例2：
$$
a = \frac {v_2 - v_1}{t_2 - t_1}
$$

$$
F = ma
$$

``` matlab
function [a F] = acc(v2, v1, t2, t1, m)
a = (v2-v1)./(t2-t1);
F = m.*a
```

```matlab
[Acc Force] = acc(20, 10, 5, 4, 1)
```

### Function Default Variables

Variable | illustration
--- | ---
inputname | Variable name of function input
mfilename | File name of currently running function
nargin | Number of function input arguments
nargout | Number of function output arguments
varargin | Variable length input argument list
varargout | Variable length output argument list

例：

```matlab
function [volume] = pillar(Do, Di, height)
if nargin == 2
	height = 1;
end
volume = abs(Do.^2-Di.^2).*height*pi/4;
```

### Function Handle

```matlab
f = @(x) exp(-2^x);
x = 0:0.1:2;
plot(x,f(x));
```

### 递归函数

```matlab
function output = fact(n)
	if n==1
		output = 1;
	else
		output = n * fact(n-1);
	end
end
```








