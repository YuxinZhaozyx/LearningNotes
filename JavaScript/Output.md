# JavaScript 输出

## 操作HTML元素

```html
<!DOCTYPE html>
<html>
<body>

<h1>我的第一张网页</h1>

<p id="demo">我的第一个段落</p>

<script>
document.getElementById("demo").innerHTML="我的第一段 JavaScript";
</script>

</body>
</html>
```

## 写到文档输出

```html
<!DOCTYPE html>
<html>
<body>

<h1>我的第一张网页</h1>

<script>
document.write("<p>我的第一段 JavaScript</p>");
</script>

</body>
</html>
```

如果在文档已完成加载后执行 document.write，整个 HTML 页面将被覆盖.