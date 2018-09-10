# 决策树(Decision Tree)

+ **优点**：计算复杂度不高，输出结果易于理解，对中间值的缺失不敏感，可以处理不相关特征数据
+ **缺点**： 可能产生过拟合的问题
+ **适用数据类型**：数值型和标称型

## ID3算法

### 信息熵与信息增益

#### 信息熵（entropy）

如果待分类的事物可能划分在多个分类中，则符号$x_i$的信息定义为
$$
l(x_i)=-log_2p(x_i)
$$
熵定义为信息的期望值，
$$
H = -\sum_{i=1}^n p(x_i)log_2 p(x_i)
$$
其中n为分类的数目。

```python
from math import log

# 计算信息熵
def calcEntropy(dataSet):
	numEntries = len(dataSet)
	labelCounts = {}
	
	# 计算各特征频数
	for featureVector in dataSet:
		currentLabel = featureVector[-1]
		if currentLabel not in labelCounts.keys():
			labelCounts[currentLabel] = 0
		labelCounts[currentLabel] += 1

	# 计算信息熵
	entropy = 0.0
	for key in labelCounts:
		prob = float(labelCounts(key))/numEntries # 求概率
		entropy -= prob * log(prob,2) # 以2为底求对数
 
	return entropy
```

### 划分数据集

```python

def splitDataSet(dataSet, axis, value):
	retDataSet = []
	# 抽取
	for featureVector in dataSet:
		if featureVector[axis] == value:
			reducedFeatureVector = featureVector[:axis]
			reducedFeatureVector.extend(featureVector[axis+1:])
			retDataSet.append(reducedFeatureVector)
	return retDataSet

def chooseBestFeatureToSplit(dataSet):
	numFeatures = len(dataSet[0]) - 1
	baseEntropy = calcEntropy(dataSet)
	bestInfoGain = 0.0
	bestFeature = -1
	for i in range(numFeatures):
		featureList = [example[i] for example in dataSet] # 第i个特征的列表
		uniqueVals = set(featureList) # 第i个特征所有可能的值
		newEntropy = 0.0
		for value in uniqueVals:
			subDataSet = splitDataSet(dataSet, i, value)
			prob = len(subDataSet)/float(len(dataSet))
			newEntropy += prob*calcEntropy(subDataSet)
		infoGain = baseEntropy - newEntropy
		if infoGain > bestInfoGain:
			bestInfoGain = infoGain
			bestFeature = i
	return bestFeature

```

### 递归构建决策树

```python
def majorityCount(classList): # 返回classList中出现最多的
	classCount = {}
	for vote in classList:
		if vote not in classCount.keys():
			calssCount[vote] = 0
		classCount[vote] += 1
	sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(i), reverse=True)
	return sortedClassCount[0][0]

def createTree(dataSet, labels):
	classList = [example[-1] for example in dataSet]
	if classList.count(classList[0]) == len(classList): # dataSet内类型全部相同
		return classList[0]
	if len(dataSet[0]) == 1: # 遍历完所有特征时返回出现最多的
		return majorityCount(classList)
	
	bestFeature = chooseBestFeatureToSplit(dataSet)
	bestFeatureLabel = labels[bestFeature]
	newTree = {bestFeatureLabel:{}}

	featureValues = [example[bestFeature] for example in dataSet]
	uniqueVals = set(featureValues)
	for value in uniqueVals:
		subLabels = labels[:bestFeature]
		subLabels.extend(labels[bestFeature+1:])
		newTree[bestFeatureLabel][value] = createTree(splitDataSet(dataSet,bestFeature,value), subLabels)

	return newTree
```

### 使用决策树分类

```python
def classify(inputTree, featureLabels, testVector):
	firstStr = inputTree.keys()[0]
	secondDict = inputTree[firstStr]

	featureIndex = featureLabels.index(firstStr)
	for key in secondDict.keys():
		if testVector[featureIndex] == key:
			if type(secondDict[key]).__name__=='dict': # 字典类型说明是颗树
				classLabel = classify(secondDict[key], featureLabels, testVector)
			else:
				classLabel = secondDict[key]
	return classLabel
```

### 决策树的储存

```python
def storeTree(inputTree, fileName):
    import pickle
    fw = open(fileName, 'w')
    pickle.dump(inputTree, fw)
    fw.close()
    
def grabTree(fileName):
    import pickle
    fr = open(fileName, 'r')
    return pickle.load(fr)
```

