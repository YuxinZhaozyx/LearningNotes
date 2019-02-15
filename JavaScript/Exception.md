# 异常

## 测试与捕捉异常

```js
try{
    //code
}
catch(err){
    //code
}
```

```js
var txt="";
function message()
{
	try{
  		adddlert("Welcome guest!");
  	}
	catch(err){
  		txt="There was an error on this page.\n\n";
  		txt+="Error description: " + err.message + "\n\n";
  		txt+="Click OK to continue.\n\n";
  		alert(txt);
  	}
}
```

## 抛出异常

```js
throw exception
```

```js
function myFunction()
{
	try{
  		var x=document.getElementById("demo").value;
  		if(x=="")    throw "empty";
  		if(isNaN(x)) throw "not a number";
  		if(x>10)     throw "too high";
  		if(x<5)      throw "too low";
  	}
	catch(err){
  		var y=document.getElementById("mess");
  		y.innerHTML="Error: " + err + ".";
  	}
}
```

