# AdaBoost

+ **优点**：泛化错误率低，易编码，可以应用在大部分分类器上，无参数调整
+ **缺点**：对离群点敏感
+ **适用数据类型**：数值型和标称型数据

## 构建弱分类器

```python
def loadSimpleData():
	dataMat = np.mat([[1.0, 2.1],[2.0,1.1],[1.3,1.0],[1.0,1.0],[2.0,1.0]])
	classLabels = [1.0, 1.0, -1.0, -1.0, 1.0]
	return dataMat, classLabels

def stumpClassify(dataMat, dimen, threshVal, threshInequal): # 决策树的简化版本,单层，弱分类器
	dataMat = np.mat(dataArr)
	retArr = np.ones((np.shape(dataMat)[0], 1))
	if threshInequal == 'lessthan':
		retArr[dataMat[:, dimen] <= threshVal] = -1.0
	else:
		retArr[dataMat[:, dimen] > threshVal] = -1.0
	return retArr

def buildStump(dataArr, classLabels, D): # 构建弱分类器，D为数据集的权重向量
	labelMat = np.mat(classLabels).T 
	m,n = np.shape(dataMat)
	numSteps = 10.0
	bestStump = {}
	bestClass = np.mat(np.zeros((m,1)))
	minError = np.inf 
	for i in range(n): # 对每一个特征
		rangeMin = dataMat[:,i].min()
		rangeMax = dataMat[:,i].max()
		stepSize = (rangeMax-rangeMin)/numSteps
		for j in range(-1, int(numSteps)+1):
			for inequal in ['lessthan','greaterthan']:
				threshVal = rangeMin + float(j) * stepSize
				predictedVals = stumpClassify(dataMat, i, threshVal, inequal)
				errorMat = np.mat(np.ones((m,1)))
				errorMat[predictedVals == labelMat] = 0
				weightedError = D.T * errorMat
				
				print "split: dim %d, thresh %.2f, thresh inequal: %s, the weighted error is %.3f" %(i, threshVal, inequal, weightedError)

				if weightedError < minError:
					minError = weightedError
					bestClass = predictedVals.copy()
					bestStump['dim'] = i
					bestStump['thresh'] = threshVal
					bestStump['inequal'] = inequal
	return bestStump, minError, bestClass

```

## 构建完整的AdaBoost分类器

**原理**：

为每个分类器分配一个权重值$\alpha$，$\alpha$由每个弱分类器的错误率$\varepsilon$计算得到。
$$
\varepsilon = \frac{未正确分类的样本数目}{所有样本数目} \\
\alpha=\frac12 \ln \left( \frac{1-\varepsilon}{\varepsilon}\right)
$$
计算出$\alpha$值后对样本集的权重向量$D$更新，使得正确分类的样本权重降低而错分样本权重提高。

如某个样本被正确分类：
$$
D_i^{new} = \frac{D_i^{old}e^{-\alpha}}{Sum(D^{new})}
$$
如果某个样本被错分：
$$
D_i^{new} = \frac{D_i^{old}e^{\alpha}}{Sum(D^{new})}
$$
**伪代码**：

```
For each iteration:
	Find the best stump using buildStump()
	Add the best stump to the stump array
	Calculate alpha
	Calculate the new weight vector – D
	Update the aggregate class estimate
	If the error rate ==0.0 : 
		break out of the for loop
```

**实现**：

```python
def AdaBoostTrainDecisionStump(dataArr, classLabels, numIter = 40):
	weakClassifierList = []
	labelMat = np.mat(classLabels).T
	m = np.shape(dataArr)[0]
	D = np.mat(np.ones((m,1))/m) # 最开始的样本权重是相同的
	aggregateClassResult = np.mat(np.zeros((m,1)))

	for i in range(numIter):
		bestStump, error, classResult = buildStump(dataArr, classLabels, D)
		print "D: " , D.T
		alpha = float(0.5*np.log((1.0-error)/max(error, 1e-16)))
		bestStump['alpha'] = alpha
		weakClassifierList.append(bestStump)
		print 'classResult: ', classResult.T
		exponent = np.multiply(-alpha*labelMat, classResult)
		D = np.multiply(D, np.exp(exponent))
		D = D / D.sum()
		aggregateClassResult += alpha*classResult
		print "aggregateClassResult: ", aggregateClassResult.T
		aggregateErrors = np.multiply(np.sign(aggregateClassResult) != labelMat, np.ones((m,1)))
		errorRate = aggregateErrors.sum()/m
		print "total error: ", errorRate, '\n'
		if errorRate == 0.0:
			break
	return weakClassifierList

```

## 分类

```python
def AdaBoostClassify(dataArr, classifierList):
	dataMat = np.mat(dataArr)
	m = np.shape(dataMat)[0]
	aggregateClassResult = np.mat(np.zeros((m,1)))
	for i in range(len(classifierList)):
		classResult = stumpClassify(dataMat, classifierList[i]['dim'], classifierList[i]['thresh'],classifierList[i]['inequal'])
		aggregateClassResult += classifierList[i]['alpha'] * classResult
		print aggregateClassResult
	return np.sign(aggregateClassResult)

```

