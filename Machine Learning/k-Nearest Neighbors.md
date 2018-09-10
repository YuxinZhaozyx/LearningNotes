# k-近邻算法（k-Nearest Neighbors ）

+ 优点：精度高、对异常值不敏感、无数据输入假定
+ 缺点：计算复杂度高、空间复杂度高
+ 适用数据范围：数值型和标称型

## 解析过程

对未知类别数据集中的每个点依次执行以下操作：

1. 计算已知类别数据集中点与当前点之间的距离
2. 按照距离递增次序排序
3. 选取与当前点距离最小的k个点
4. 确定前k个点所在类别的出现频率
5. 返回前k个点出现频率最高的类别作为当前点的预测分类

### python实现

```python
#coding=utf-8
import numpy as np
import operator # 运算符模块

def createDataSet(): 
	group = np.array([[1.0,1.1],[1.0,1.0],[0.0,0.0],[0.0,0.1]])
	labels = ['A','A','B','B']
	return group, labels

def classify0(inX, dataSet, labels, k):
	dataSetSize = dataSet.shape[0]

	# 距离计算
	diffMat = np.tile(inX, (dataSetSize, 1) ) - dataSet # numpy.tile(A,reps)重复A使维度扩充为reps
	sqDiffMat = diffMat**2
	sqDistances = sqDiffMat.sum(axis=1)
	distances = sqDistances**0.5

	# 选择距离最小的k个点
	sortedDistIndicies = distances.argsort()
	classCount = {}
	for i in range(k):
		voteIlabel = labels[sortedDistIndicies[i]]
		classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1 # dict.get(key, default=None) 返回指定键的值，若无则返回default值
	sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(1), reverse=True) # operator.itemgetter(1)返回获取对象第一个域(从第0开始算)的值的函数对象，reverse决定升降序(默认为false(升序))

	return sortedClassCount[0][0]


if __name__ == '__main__':
	group,labels = createDataSet()
	print classify0([0,0],group,labels,3)
```

## 从文件读入数据

```python
def file2matrix(fileName): # 将数据从文件读到Numpy
	fr = open(fileName)
	arrayOLines = fr.readlines()
	numberOfLines = len(arrayOLines)
	returnMat = np.zeros((numberOfLines, 3))
	classLabelVector = []
	index = 0
	for line in arrayOLines:
		line = line.strip()
		listFromLine = line.split('\t')
		returnMat[index,:] = listFromLine[0:3]
		classLabelVector.append(int(listFromLine[-1]))
		index += 1
	return returnMat, classLabelVector

```

## 归一化特征

为防止数值大的属性对计算结果的影响较大，需对特征进行归一化

```python
def autoNorm(dataSet): # 归一化特征值
	minVals = dataSet.min(0) # array.min()取到所有值中的最小值，array.min(axis=0)取到每列中的最小值，array.min(axis=1)渠道每一行中的最小值
	maxVals = dataSet.max(0)
	ranges = maxVals - minVals
	normDataSet = np.zeros(np.shape(dataSet))
	m = dataSet.shape[0]
	normDataSet = (dataSet - np.tile(minVals, (m,1))) / np.tile(ranges,(m,1))
	return normDataSet, ranges, minVals

```

注：NumPy中`/`表示矩阵点除，`linalg.solve(matA,matB)`表示矩阵除法

## 测试

```python
def datingClassTest():
	hoRatio = 0.10 # 测试集比例10%
	datingDataMat, datingLabels = file2matrix('datingTestSet2.txt')
	normMat, ranges, minVals = autoNorm(datingDataMat)
	m = normMat.shape[0]
	numTestVecs = int(m*hoRatio)
	errorCount = 0.0
	for i in range(numTestVecs):
		classifierResult = kNN.classify0(normMat[i,:], normMat[numTestVecs:m,:], datingLabels[numTestVecs:m], 3)
		print "the classifier came back with: %d, the real answer is: %d" %(classifierResult, datingLabels[i])
		if classifierResult != datingLabels[i]:
			errorCount += 1.0
	print "the total error rate is: %f" %(errorCount/float(numTestVecs))

```

