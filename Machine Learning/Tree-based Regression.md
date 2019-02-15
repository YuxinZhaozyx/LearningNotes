# 树回归

## CART(Classification And Regression Trees, 分类回归树)

### 回归树

```python
def LoadDataSet(fileName):
	dataList = []
	fr = open(fileName)
	for line in fr.readlines():
		curLine = line.strip().split('\t')
		floatLine = map(float, curLine)
		dataList.append(floatLine)
	return dataList

def BinarySplitDataSet(dataMat, feature, value):
	mat0 = dataMat[np.nonzero(dataMat[:,feature] > value)[0],:]
	mat1 = dataMat[np.nonzero(dataMat[:,feature] <=value)[0],:]
	return mat0, mat1

def RegLeaf(dataMat):
	return np.mean(dataMat[:,-1])

def RegErr(dataMat):
	return np.var(dataMat[:,-1]) * np.shape(dataMat)[0]

def CreateTree(dataMat, leafType=RegLeaf, errType=RegErr, ops=(1,4)):
	feature, value = ChooseBestSplit(dataMat, leafType, errType, ops)
	if feature == None:
		return value
	returnTree = {}
	returnTree['splitIndex'] = feature
	returnTree['splitValue'] = value
	leftSet, rightSet = BinarySplitDataSet(dataMat, feature, value)
	returnTree['left'] = CreateTree(leftSet, leafType, errType, ops)
	returnTree['right']= CreateTree(rightSet,leafType, errType, ops)
	return returnTree

def ChooseBestSplit(dataMat, leafType=RegLeaf, errType=RegErr, ops=(1,4)):
	tolerateS = ops[0] # 容许的最小的误差下降值
	tolerateN = ops[1] # 容许的最小样本数

	# 如果所有值相等则退出
	if len(set(dataMat[:,-1].T.tolist()[0])) == 1:
		return None, leafType(dataMat)

	m,n = np.shape(dataMat)
	S = errType(dataMat)
	bestS = np.inf 
	bestIndex = 0
	bestValue = 0
	for featureIndex in range(n-1):
		for splitValue in set(dataMat[:, featureIndex].T.tolist()[0]):
			mat0, mat1 = BinarySplitDataSet(dataMat, featureIndex, splitValue)
			if np.shape(mat0)[0] < tolerateN or np.shape(mat1)[0] < tolerateN:
				continue

			newS = errType(mat0) + errType(mat1)
			if newS < bestS:
				bestIndex = featureIndex
				bestValue = splitValue
				bestS = newS

	# 如果误差减小不大则退出
	if S - bestS < tolerateS: 
		return None, leafType(dataMat)

	# 如果切分出来的数据集很小则提出
	mat0, mat1 = BinarySplitDataSet(dataMat, bestIndex, bestValue)
	if np.shape(mat0)[0] < tolerateN or np.shape(mat1)[0] < tolerateN:
		return None, leafType(dataMat)

	return bestIndex, bestValue

```

### 树剪枝

一棵树如果节点过多，表明该模型可能对数据进行了“过拟合”。

通过降低决策树的复杂度来避免过拟合的过程称为剪枝(pruning)。

#### 后剪枝(postpruning)

后剪枝需将数据分为训练集和测试集。

```python
def isTree(obj):
	return type(obj).__name__=='dict'

def getMean(tree):
	if isTree(tree['right']):
		tree['right'] = getMean(tree['right'])
	if isTree(tree['left']):
		tree['left'] = getMean(tree['left'])
	return (tree['left'] + tree['right'])/2.0

def Prune(tree, testData): # 剪枝
	if np.shape(testData)[0] == 0: # 没有测试数据则进行塌陷处理
		return getMean(tree)

	if isTree(tree['right']) or isTree(tree['left']):
		leftSet, rightSet = BinarySplitDataSet(testData, tree['splitIndex'], tree['splitValue'])
	if isTree(tree['left']):
		tree['left'] = Prune(tree['left'], leftSet)
	if isTree(tree['right']):
		tree['right']= Prune(tree['right'], rightSet)

	if not isTree(tree['left']) and not isTree(tree['right']):
		leftSet, rightSet = BinarySplitDataSet(testData, tree['splitIndex'], tree['splitValue'])
		errorNoMerge = np.sum(np.power(leftSet[:,-1] - tree['left'], 2)) + np.sum(np.power(rightSet[:,-1] - tree['right'], 2))
		treeMean =(tree['left'] + tree['right'])/2.0
		errorMerge = np.sum(np.power(testData[:,-1] - treeMean, 2))
		if errorMerge < errorNoMerge:
			print 'merging'
			return treeMean
		else:
			return tree
	else:
		return tree
```

### 模型树

```python
def linearSolve(dataMat):
	m,n = np.shape(dataMat)
	X = np.mat(np.ones((m,n)))
	Y = np.mat(np.ones((m,1)))
	X[:,1:n] = dataMat[:, 0:n-1]
	Y = dataMat[:,-1]
	xTx = X.T*X
	if np.linalg.det(xTx) == 0.0:
		raise NameError('This matrix is singular, cannot do inverse, try increasing the second value of ops')

	w = xTx.I * (X.T * Y)
	return w, X, Y

def ModelLeaf(dataMat):
	w, X, Y = linearSolve(dataMat)
	return w

def ModelErr(dataMat):
	w, X, Y = linearSolve(dataMat)
	yHat = X * w
	return np.sum(np.power(Y-yHat,2))

```

### 预测

```python
def RegTreeEval(model, inData):
	return float(model)

def ModelTreeEval(model, inData):
	n = np.shape(inData)[1]
	X = np.mat(np.ones((1,n)))
	X[:, 1:n] = inData[:,:-1]
	return float(X*model)

def TreeForecast(tree, inData, modelEval=RegTreeEval):
	if not isTree(tree):
		return modelEval(tree, inData)
	if inData[:,tree['splitIndex']] > tree['splitValue']:
		if isTree(tree['left']):
			return TreeForecast(tree['left'], inData, modelEval)
		else:
			return modelEval(tree['left'], inData)
	else:
		if isTree(tree['right']):
			return TreeForecast(tree['right'], inData, modelEval)
		else:
			return modelEval(tree['right'], inData)

def CreateForecast(tree, testMat, modelEval=RegTreeEval):
	m = np.shape(testMat)[0]
	yHat = np.mat(np.zeros((m,1)))
	for i in range(m):
		yHat[i] = TreeForecast(tree, testMat[i,:], modelEval)
	return yHat
```

