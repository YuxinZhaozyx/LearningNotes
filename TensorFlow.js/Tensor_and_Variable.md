# 张量和变量

张量(Tensor)和变量(Variable)是TensorFlow.js中数据的主要表现形式，两者的不同之处在于张量是不可变的，而变量是可变的。

## 张量

Tensorflow.js中数据的主要表现形式就是**tensor（张量）**：由 **一组数值形成一维或多维数组**。一个Tensor实例有一个**shape属性来定义这一组数值如何组成张量,**而最主要的Tensor实例的构造函数就是 `tf.tensor` 函数

```js
// 2x3 Tensor
const shape = [2, 3]; // 2 行, 3 列
const a = tf.tensor([1.0, 2.0, 3.0, 10.0, 20.0, 30.0], shape);
a.print(); // 打印张量值
// 输出:    [[1 , 2 , 3 ],
//          [10, 20, 30]]

// shape也可以用下面的方式实现:
const b = tf.tensor([[1.0, 2.0, 3.0], [10.0, 20.0, 30.0]]);
b.print();
// 输出:    [[1 , 2 , 3 ],
//          [10, 20, 30]]
```

但是，为了构造低秩张量，我们推荐使用下面的函数来增强代码的可读性：`tf.scalar`（零维）, `tf.tensor1d`（一维）, `tf.tensor2d`（二维）, `tf.tensor3d`（三维）、`tf.tensor4d`（四维）以及 `tf.ones`（值全是1）或者`tf.zeros`（值全是0）

```js
const a = tf.scalar(3.14);
a.print(); // 输出零维张量

const b = tf.tensor2d([[2, 3, 4], [5, 6, 7]]);
b.print(); // 输出二维张量

const c = tf.zeros([2, 3]);
c.print(); // 输出2行3列的值全是0的张量

const d = tf.ones([3, 5]);
d.print(); // 输出3行5列的值全是1的张量
```

在TensorFlow.js中，张量是不变的; 一旦创建你就不能改变它们的值。 但是，您可以对它们执行操作来生成新的张量。



## 变量

Variables变量是通过张量进行初始化得到的。不像Tensor的值不可变，变量的值是可变的。你可以**使用变量的`assign`方法分配一个新的tensor到这个变量上，这是变量就会改变**：

```js
const initialValues = tf.zeros([5]);
const biases = tf.variable(initialValues); // 初始化biases
biases.print(); // 输出: [0, 0, 0, 0, 0]

const updatedValues = tf.tensor1d([0, 1, 0, 1, 0]);
biases.assign(updatedValues); // 更新 biases的值
biases.print(); // 输出: [0, 1, 0, 1, 0]
```

首先使用`tf.zeros`得到一个张量，然后**利用这个张量初始化得到一个变量，**接着我们就可以打印这个变量，并且通`Object.prototype.toString.call(biases)`方法可以判断变量也是一个对象，接着，**我们再生成一个张量，然后变量调用`assign`方法传入这个张量**，就可以得到一个新的变量了。

由此我们可以得出一个结论：**变量由张量生成，且张量不可变而变量可变。**

