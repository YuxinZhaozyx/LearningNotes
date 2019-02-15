# 模型

在Tensorflow.js中，从概念上来说，一个模型就是一个给定一些输入将会产生特定的输出的函数。简单来说，**一个模型就是一个函数**，只是它完成了特定的任务。

在TensorFlow.js中有两种方式来创建模型，一种是通过操作（ops）来直接完成模型本身所做的工作，另外一种就是通过高级API `tf.model`来创建一个模型，显然第二种是更容易的。

## 通过操作（ops）构建模型

```js
function predict(input) {
  // y = a * x ^ 2 + b * x + c
  // More on tf.tidy in the next section
  return tf.tidy(() => {
    const x = tf.scalar(input);

    const ax2 = a.mul(x.square());
    const bx = b.mul(x);
    const y = ax2.add(bx).add(c);

    return y;
  });
}

const a = tf.scalar(2);
const b = tf.scalar(4);
const c = tf.scalar(8);

const result = predict(2);
result.print() 
```

## 通过高级API `tf.model`来创建模型

`tf.model` 方法（这里的model并不是真正可以调用的方法，而是一个总称，比如实际上可以调用的是`tf.sequential`模型），这在深度学习中是非常流行的概念。 下面的代码就创建了 `tf.sequential` 模型(不完整版)：

```js
const model = tf.sequential();
model.add(
  tf.layers.simpleRNN({
    units: 20,
    recurrentInitializer: 'GlorotNormal',
    inputShape: [80, 4]
  })
);

const optimizer = tf.train.sgd(LEARNING_RATE);
model.compile({optimizer, loss: 'categoricalCrossentropy'});
model.fit({x: data, y: labels)});
```

