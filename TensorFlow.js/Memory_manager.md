内存管理

因为TensorFlow.js使用了GPU来加速数学运算，因此当tensorflow处理张量和变量时就有必要来管理GPU内存。在TensorFlow.js中，我们可以通过`dispose` 和 `tf.tidy`这两种方法来管理内存。

## `dispose`

您可以在张量或变量上调用`dispose`来清除它并释放其GPU内存：

```js
const x = tf.tensor2d([[0.0, 2.0], [4.0, 6.0]]);
const x_squared = x.square();
const v = tf.variable(x);

x.dispose();
x_squared.dispose();
v.dispose();
```

## `tf.tidy`

进行大量的张量操作时使用`dispose`可能会很麻烦。 TensorFlow.js提供了另一个函数`tf.tidy`，它对JavaScript中的常规范围起到类似的作用，不同的是它针对GPU支持的张量。

**`tf.tidy`执行一个函数并清除所有创建的中间张量，释放它们的GPU内存。 它不清除内部函数的返回值。**

```js
const average = tf.tidy(() => {
  const y = tf.tensor1d([1.0, 2.0, 3.0, 4.0]);
  const z = tf.ones([4]);

  return y.sub(z).square().mean();
});

average.print()
```

## 注意

传递给`tf.tidy`的函数应该是同步的，并且不会返回Promise。我们建议在`tf.tidy`内不要有更新UI或在发出远程请求的代码。

`tf.tidy`不会清理变量。变量通常持续到机器学习模型的整个生命周期，因此TensorFlow.js不会清理它们，即使它们是在tidy中创建的。不过，您可以手动调用`dispose`处理它们。

