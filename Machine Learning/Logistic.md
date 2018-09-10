# Logistic回归

+ **优点**：计算代价不高，易于理解和实现。
+ **缺点**：容易欠拟合，分类精度可能不高。
+ **适用数据类型**：数值型和标称型数据。

## Sigmoid函数

$$
\sigma(z) = \frac{1}{1+e^{-z}}
$$

Sigmoid函数是一种阶跃函数(step function)。在数学中，如果实数域上的某个函数可以用半开区间上的指示函数的有限次线性组合来表示，那么这个函数就是阶跃函数。而数学中指示函数(indicator function)是定义在某集合X上的函数，表示其中有哪些元素属于某一子集A。

为实现Sigmoid回归分类器，我们可以在每个特征上都乘以一个回归系数，然后把所有的结果值相加，将这个总和代入Sigmoid函数中，进而得到一个范围在0-1之间的数值。任何大于0.5的数据被分入1类，小于0.5即被归入0类。

## 基于最优化方法的最佳回归系数确定

Sigmoid函数的输入记为z，
$$
z=w_0x_0+w_1x_1+...+w_nx_n=\bold{w^Tx} \\
\bold{w}=(w_0,w_1,...,w_n) \\
\bold{x}=(x_0,x_1,...,x_n)
$$
向量$\bold{x}$为分类器的输入数据，向量$\bold{w}$为将要求得的最佳参数。

### 梯度上升法(gradient ascent)

**基本思想**：沿着该函数的梯度方向探寻最大值。

函数$f(x,y)$的梯度：
$$
\nabla f(x,y)=
\begin{bmatrix}
\frac{\part f(x,y)}{\part x} \\
\frac{\part f(x,y)}{\part y} 
\end{bmatrix}
$$
**梯度上升法**迭代公式：
$$
w = w+\alpha \nabla_wf(w)
$$
**梯度下降法**迭代公式：
$$
w=w-\alpha \nabla_w f(w)
$$
**注**：梯度上升法用于求函数最大值，梯度下降法用于求函数最小值

#### 梯度求法

考虑二分类问题

预测函数为：
$$
h_w(x) = \sigma(w^T x) = \frac{1}{1+e^{-w^Tx}}
$$
$h_w(x)$的值表示$y=1$的概率，因此分类结果为类别1和类别0的概率分别为： 
$$
P(y=1|x;w) =h_w(x) \\
P(y=0| x;w)= 1-h_w(x)
$$
合并为：
$$
P(y|x;w) = (h_w(x))^y(1-h_w(x))^{1-y}
$$
其似然函数为：
$$
L(w) = \prod_{i=1}^{m}P(y_i|x_i;w) = \prod_{i=1}^m (h_w(x_i))^{y_i}(1-h_w(x_i))^{1-y_i}
$$
取对数：
$$
f(w) = logL(w) = \sum_{i=1}^m (y_i log h_w(x_i)+(1-y_i)log(1-h_w(x_i)))
$$
要使正确的概率最大，则利用最大似然估计使得$f(w)$取值最大时的$w$。
$$
\begin{align}
\frac{\part f(w)}{\part w_j} 
& = \sum_{i=1}^m(y_i \frac{1}{h_w(x_i)} \frac{\part h_w(x_i)}{\part w_j}-(1-y_i)\frac{1}{1-h_w(x_i)}\frac{\part h_w(x_i)}{\part w_j})  \\
&=  \sum_{i=1}^m(y_i \frac{1}{\sigma(w^T x_i)} \frac{\part \sigma(w^T x_i)}{\part w_j}-(1-y_i)\frac{1}{1-\sigma(w^T x_i)}\frac{\part \sigma(w^T x_i)}{\part w_j})  \\
& =  \sum_{i=1}^m(y_i \frac{1}{\sigma(w^T x_i)} \frac{\part \sigma(w^T x_i)}{\part w_j}-(1-y_i)\frac{1}{1-\sigma(w^T x_i)})\sigma(w^T x_i) (1-\sigma(w^T x_i))  \frac{\part w^T x_i}{\part w_j}) \\
&= \sum_{i=1}^m (y_i(1-\sigma(w^T x_i))-(1-y_i)\sigma(w^T x_i))x_{ij}  \\
&= \sum_{i=1}^m (y_i - \sigma(w^T x_i))x_{ij} \\
&= \sum_{i=1}^m(y_i - h_w(x_i))x_{ij}
\end{align}
$$

#### 训练算法：使用梯度上升法找到最佳参数

```python
import numpy as np

def loadDataSet():
	dataMat = []
	labelMat = []
	fr = open('testSet.txt')
	for line in fr.readlines():
		lineArr = line.strip().split() # 按空白分割
		dataMat.append([1.0, float(lineArr[0]), float(lineArr[1])])
		labelMat.append(int(lineArr[2]))
	return dataMat, labelMat

def sigmoid(z):
	return 1.0/(1+np.exp(-z))

def gradientAscent(dataMatIn, classLabels): # 梯度上升
	dataMatrix = np.mat(dataMatIn)
	labelMat = np.mat(classLabels).transpose()
	m,n = np.shape(dataMatrix)
	alpha = 0.001 # 移动步长
	maxCycles = 500 # 最大迭代次数
	weights = np.ones((n,1)) # 待优化参数
	for k in range(maxCycles):
		h = sigmoid(dataMatrix*weights)
		error = labelMat - h
		weights = weights + alpha*dataMatrix.transpose()*error
	return weights

```

### 随机梯度上升(stochastic gradient ascent)

随机梯度上升算法一次仅用一个样本点来更新回归系数，可以在新样本到来时对分类器进行增量更新。

```python
def stochasticGradientAscent0(dataMatIn, classLabels):
	dataMatrix = np.mat(dataMatIn)
	m,n = np.shape(dataMatrix)
	alpha = 0.001
	weights = np.ones((n,1))
	for i in range(m):
		h = sigmoid(np.sum(dataMatrix[i]*weights))
		error = classLabels[i] - h
		weights = weights + alpha*error*dataMatrix[i].transpose()
	return weights
```

改进后：

```python
def stochasticGradientAscent(dataMatIn, classLabels, numIter=150):
	dataMatrix = np.mat(dataMatIn)
	m,n = np.shape(dataMatrix)
	weights = np.ones((n,1))

	for j in range(numIter):
		dataIndex = range(m)
		for i in range(m):
			alpha = 4/(1.0+j+i)+0.01 # 每次迭代调整alpha
			randomIndex = int(random.uniform(0,len(dataIndex))) # 随机更新
			h = sigmoid(np.sum(dataMatrix[randomIndex]*weights))
			error = classLabels[randomIndex] - h
			weights = weights + alpha*error*dataMatrix[randomIndex].transpose()
			del(dataIndex[randomIndex])
	return weights
```

## 准备数据

对于Logistic算法，若数据中有缺失值，只需将该值用0填补，Logistic仅仅不更新weights中该项而没有其他影响。

## 分类

```python
def classifyVector(inX, weights):
	prob = sigmoid(np.sum(inX*weights))
	if prob > 0.5:
		return 1.0
	else:
		return 0.0
```

## 测试

```python
def test():
	frTrain = open('horseColicTraining.txt')
	frTest = open('horseColicTest.txt')
	trainingSet = []
	trainingLabels = []
	for line in frTrain.readlines():
		currLine = line.strip().split('\t')
		lineArr = []
		for i in range(21):
			lineArr.append(float(currLine[i]))
		trainingSet.append(lineArr)
		trainingLabels.append(float(currLine[21]))
	trainWeights = stochasticGradientAscent(trainingSet, trainingLabels, 500)
	errorCount = 0
	numTestVec = 0.0
	for line in frTest.readlines():
		numTestVec += 1.0
		currLine = line.strip().split('\t')
		lineArr = []
		for i in range(21):
			lineArr.append(float(currLine[i]))
		if int(classifyVector(np.array(lineArr), trainWeights)) != int(currLine[21]):
			errorCount += 1
	errorRate = (float(errorCount)/numTestVec)
	print "the error rate of this test is: %f" % errorRate
	return errorRate
```

