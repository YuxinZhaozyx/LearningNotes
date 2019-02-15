# 预测数值型数据：回归(regression)

## 线性回归(linear regression)

+ **优点**：结果易于理解，计算上不复杂
+ **缺点**：对非线性的数据拟合不好
+ **适用数据类型**：数值型和标称型数据

记输入数据矩阵 $\boldsymbol X$ , 回归系数向量 $\boldsymbol w $，预测结果向量 $ \boldsymbol Y$
$$
\boldsymbol Y = \boldsymbol{ X^T w}
$$
找出使误差最小的 $\boldsymbol W$ ，采用平方误差
$$
\boldsymbol{(Y-X^Tw)^T(Y-X^Tw)}
$$
对$\boldsymbol W$求导得
$$
\boldsymbol {X^T(Y-X^Tw)}
$$
令其等于零，得
$$
\boldsymbol{\hat w = (X^TX)^{-1}X^Ty}
$$

```python
def loadDataSet(fileName):
	fr = open(fileName)
	dataList = []
	labelList = []
	for line in fr.readlines():
		tokenList = line.strip().split('\t')
		tokenList = map(float, tokenList)
		dataList.append(tokenList[:-1])
		labelList.append(tokenList[-1])
	return dataList, labelList

def standardRegression(xList, yList):
	xMat = np.mat(xList)
	yMat = np.mat(yList).T 
	xTx = xMat.T * xMat
	'''
	if np.linalg.det(xTx) == 0.0:
		print "This matrix is singular, cannot do inverse."
		return
	w = xTx.I * (xMat.T * yMat)
	'''
	w = np.linalg.solve(xTx, xMat.T * yMat) # 解决了矩阵没有逆矩阵的情况
	return w

```

## 局部加权线性回归函数(Locally Weighted Linear Regression, LWLR)

使用核来赋予附近的点更高的权重。核的类型可以只有选择，最常用的核是高斯核：
$$
\boldsymbol W(i,i) = \exp\left(\frac{\|x^{(i)}-x\|^2}{-2 \sigma^2} \right)
$$
回归系数：
$$
\boldsymbol{\hat w = (X^TWX)^{-1}X^TWy}
$$

```python
def LWLR(testPoint, xList, yList, sigma=1.0):
	xMat = np.mat(xList)
	yMat = np.mat(yList).T
	m = np.shape(xMat)[0]
	weights = np.mat(np.eye((m)))
	for j in range(m):
		diffMat = testPoint - xMat[j,:]
		weights[j,j] = np.exp(diffMat*diffMat.T / (-2.0*(sigma**2)))
	xTx = xMat.T * weights * xMat
	'''
	if np.linalg.det(xTx) == 0.0:
		print "This matrix is singular, cannot do inverse."
		return
	w = xTx.I * (xMat.T * weights * yMat)
	'''
	w = np.linalg.solve(xTx, xMat.T * weights * yMat) 
	return testPoint * w 
```

$\sigma$取较小值时，可以得到很好的近似，但$\sigma$过小时会考虑过多噪声，进而导致过拟合现象

## 缩减(shrinkage)系数来“理解”数据

如果数据的特征比样本点还多则之前的方法不再奏效，因为$X^TX$时不存在逆矩阵。

### 岭回归法(ridge regression)

岭回归就是在$X^TX$上加上一个$\lambda E$使得矩阵非奇异，进而可对$X^TX + \lambda E$求逆，$E$ 为m*m的单位矩阵，回归系数变成:
$$
\boldsymbol{\hat w = (X^TX+\lambda E)^{-1}X^Ty}
$$


```python
def RidgeRegression(xMat, yMat, lambd=0.2):
	xTx = xMat.T * xMat
	denom = xTx + np.eye(np.shape(xMat)[1])*lambd
	if np.linalg.det(denom) == 0.0:
		print "This matrix is singular, cannot do inverse."
		return
	w = denom.I * (xMat.T * yMat)
	return w

def RidgeRegressionTest(xList, yList):
	xMat = np.mat(xList)
	yMat = np.mat(yList).T
	yMat = yMat - np.mean(yMat, axis=0)
	xMean = np.mean(xMat, axis=0)
	xVar = np.var(xMat, axis=0)
	xMat = (xMat - xMean)/xVar # 将每个特征标准化
	numTestPoints = 30
	wMat = np.zeros((numTestPoints, np.shape(xMat)[1]))
	for i in range(numTestPoints):
		w = RidgeRegression(xMat, yMat, np.exp(i-10))
		wMat[i,:] = w.T
	return wMat

```

通过不断选取不同的$\lambda$来重复上述测试过程，最终得到一个使预测误差最小的$\lambda$

### lasso法

用约束条件$\sum_{k=1}^N |w_k| \le \lambda$取代$\sum_{k=1}^N w_k^2 \le \lambda$

需要使用二次规划算法

### 前向逐步回归

前向逐步回归算法可以得到核lasso算法差不多的效果，但更简单。它属于一种贪心算法，即每一步都尽可能地减小误差。一开始，所有的权重都设为1，然后每一步所做出的决策是对某个权重增加或减少一个很小的值。

**伪代码**：

```
Regularize the data to have 0 mean and unit variance
For every iteration:
	Set lowestError to +inf
	For every feature:
		For increasing and decreasing:
			Change one coefficient to get a new W
			Calculate the Error with new W
			If the Error is lower than lowestError: set Wbest to the current W
		Update set W to Wbest
```

**python实现**：

```python
def RSSError(yArr, yMatArr):
	return ((yArr-yMatArr)**2).sum()

def StageWise(xArr, yArr, eps=0.01, numIter=100):
	xMat = np.mat(xArr)
	xMean = np.mean(xMat,0)
	xVar = np.var(xMat,0)
	xMat = (xMat - xMean)/xVar

	yMat = np.mat(yArr).T
	yMean = np.mean(yMat,0)
	yMat = yMat - yMean

	m,n = np.shape(xMat)
	returnMat = np.zeros((numIter,n))
	w = np.zeros((n,1))
	wMax = w.copy()

	for i in range(numIter):
		print w.T
		lowestError = np.inf
		for j in range(n):
			for sign in [-1,1]:
				wTest = w.copy()
				wTest[j] += eps*sign
				yTest = xMat*wTest
				rssE = RSSError(yMat.A, yTest.A)
				if rssE < lowestError:
					lowestError = rssE
					wMax = wTest
		w = wMax.copy()
		returnMat[i,:] = w.T
	return returnMat
```

