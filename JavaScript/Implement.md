# JavaScript 实现

## HTML中的脚本

### `<script>`标签

如需在HTML页面中插入JavaScript，需使用`<script>`标签。

```html
<script>
alert("Hello world");
</script>
```

### `<body>`中的JavaScript

在文档加载时写文本。

```html
<!DOCTYPE html>
<html>
<body>
.
<script>
document.write("<h1>This is a heading</h1>");
document.write("<p>This is a paragraph</p>");
</script>
.
</body>
</html>
```

**注：** 只能在 HTML 输出中使用 document.write。如果您在文档加载后使用该方法，会覆盖整个文档。

### JavaScript函数

脚本可位于 HTML 的 `<body>` 或 `<head>` 部分中，或者同时存在于两个部分中。

通常的做法是把函数放入 `<head>` 部分中，或者放在页面底部。这样就可以把它们安置到同一处位置，不会干扰页面的内容。

#### `<head>`中的JavaScript函数

```html
<!DOCTYPE html>
<html>

<head>
<script>
function myFunction()
{
document.getElementById("demo").innerHTML="My First JavaScript Function";
}
</script>
</head>

<body>

<h1>My Web Page</h1>

<p id="demo">A Paragraph</p>

<button type="button" onclick="myFunction()">Try it</button>

</body>
</html>
```

#### `<body>`中的JavaScript函数

```html
<!DOCTYPE html>
<html>
<body>

<h1>My Web Page</h1>

<p id="demo">A Paragraph</p>

<button type="button" onclick="myFunction()">Try it</button>

<script>
function myFunction()
{
document.getElementById("demo").innerHTML="My First JavaScript Function";
}
</script>

</body>
</html>
```

## 外部的JavaScript脚本

也可以把脚本保存到外部文件中。外部文件通常包含被多个网页使用的代码。

外部 JavaScript 文件的文件扩展名是 `.js`。

如需使用外部文件，请在` <script> `标签的 `src` 属性中设置该 .js 文件：

```html
<!DOCTYPE html>
<html>
<body>
<script src="myScript.js"></script>
</body>
</html>
```

