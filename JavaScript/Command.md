# if...else

```js
if(condition)
{
    //code
}
else if(condition)
{
    //code
}
else
{
    //code
}
```

# switch

```js
switch(n)
{
case 1:
    //code
    break;
case 2:
    //code
    break;
default:
	//code        
}
```

# for

```js
for(var i=0; i<cars.length; i++)
{
	document.write(cars[i] + "<br>");   
}
```

```js
// 遍历对象属性
var txt="";
var person = {firstName:"John", lastName:"Doe", age:25};
for(var x in person)
{
    txt = txt + person[x];
}
```

# while

```js
while(condition)
{
    //code
}
```

# do while

```js
do{
    //code
}while(condition);
```

# break, continue

```js
for(i=0; i<10; i++){
    if(i==3) continue;
    else if(i==5) break;
}
```

## JavaScript标签

```js
labelname:
	code
```

```js
break labelname;
continue labelname;
```

```js
cars=["BMW","Volvo","Saab","Ford"];
list:
{
	document.write(cars[0] + "<br>");
	document.write(cars[1] + "<br>");
	document.write(cars[2] + "<br>");
	break list;
	document.write(cars[3] + "<br>");
	document.write(cars[4] + "<br>");
	document.write(cars[5] + "<br>");
}
```

通过标签引用，break 语句可用于跳出任何 JavaScript 代码块