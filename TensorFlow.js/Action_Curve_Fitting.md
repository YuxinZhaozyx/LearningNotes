# 实战：曲线拟合

## 详细代码

```shell
$ git clone https://github.com/tensorflow/tfjs-examples
$ cd tfjs-examples/polynomial-regression-core
$ yarn
$ yarn watch
```

## 输入数据

假设该数据可用$y=ax^3+bx^2+cx+d$拟合。

## 学习步骤

### 设置变量

此处变量为未知量$a,b,c,d$。

```js
const a = tf.variable(tf.scalar(Math.random()));
const b = tf.variable(tf.scalar(Math.random()));
const c = tf.variable(tf.scalar(Math.random()));
const d = tf.variable(tf.scalar(Math.random()));
```

### 建立模型

```js
function predict(x){
    // y = a*x^3 + b*x^2 + c*x + d
    return tf.tidy(()=>{
        return a.mul(x.pow(tf.scalar(3)))
        	.add(b.mul(x.square()))
        	.add(c.mul(x))
        	.add(d);
    });
}
```

### 训练模型

最后一步就是要训练这个模型使得系数和这些散点更加匹配，而为了训练模型，我们需要定义下面的三样东西：

- 损失函数（loss function）：这个损失函数代表了给定多项式和数据的匹配程度。 损失函数值越小，那么这个多项式和数据就跟匹配。
- 优化器（optimizer）：这个优化器实现了一个算法，它会基于损失函数的输出来修正系数值。所以优化器的目的就是尽可能的减小损失函数的值。
- 训练迭代器（training loop）：即它会不断地运行这个优化器来减少损失函数。

所以，上面这三样东西的 关系就非常清楚了： 训练迭代器使得优化器不断运行，使得损失函数的值不断减小，以达到多项式和数据尽可能匹配的目的。这样，最终我们就可以得到a、b、c、d较为精确的值了。

#### 损失函数(loss function)

此处我们使用**MSE（均方误差，mean squared error）**作为损失函数。

```js
function loss(predictions, labels){
    const meanSquareError = predictions.sub(labels).square().mean();
    return meanSquareError;
}
```

#### 优化器(optimizer)

对于我们的优化器而言，我们选用 ** SGD(Stochastic Gradient Descent)** 优化器，即随机梯度下降。SGD的工作原理就是利用数据中任意的点的梯度以及使用它们的值来决定增加或者减少我们模型中系数的值。

TensorFlow.js提供了一个很方便的函数用来实现SGD，所以你不需要担心自己不会这些特别复杂的数学运算。 即 `tf.train.sgd` 将一个学习率（learning rate）作为输入，然后返回一个`SGDOptimizer`对象，它与优化损失函数的值是有关的。

在提高它的预测能力时，学习率（learning rate）会控制模型调整幅度将会有多大。低的学习率会使得学习过程运行的更慢一些（更多的训练迭代获得更符合数据的系数），而高的学习率将会加速学习过程但是将会导致最终的模型可能在正确值周围摇摆。简单的说，你既想要学的快，又想要学的好，这是不可能的。

下面的代码就创建了一个学习率为0.5的SGD优化器。

```js
const learningRate = 0.5;
const optimizer = tf.train.sgd(learningRate);
```

#### 训练循环(training loop)

```js
function train(xs, ys, numIterations = 75){
    const learningRate = 0.5;
    const optimizer = tf.train.sgd(learningRate);
    
    for(let iter=0; iter<numIterations; iter++){
        optimizer.minimize(()=>{
            const predictYs = predict(xs);
            return loss(predictYs, ys);
        });
    }
}
```

`minimize` 接受了一个函数作为参数，这个函数做了下面的两件事情：

1. 首先它对所有的x值通过我们在之前定义的`predict`函数预测了y值。

2. 然后它通过我们之前定义的损失函数返回了这些预测的均方误差。

`minimize`函数之后会自动调整这些变量（即系数a、b、c、d）来使得损失函数更小。

