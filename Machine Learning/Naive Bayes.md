# 朴素贝叶斯(Naive Bayes)

+ **优点**：在数据较少的情况下仍然有效，可以处理多类别问题。
+ **缺点**：对于输入数据的准备方式较敏感。
+ **适用数据类型**：标称型数据。

## 贝叶斯公式


假设数据为$(x,y)$,它有两个类别，$p1(x,y)$表示(x,y)属于类别1的概率，$p2(x,y)$表示(x,y)属于类别2的概率。

+ 如果$p1(x,y)>p2(x,y)$则(x,y)属于类别1
+ 如果$p1(x,y)<p2(x,y)$则(x,y)属于类别2



$$
p(c|\bold{w}) = \frac{p(x|\bold{w})p(c)}{p(\bold{w})}
$$

$$
p(c_i|x,y) = \frac{p(x,y|c_i)p(c_i)}{p(x,y)}
$$

c代表类别，则$p(c_i|x,y)$表示(x,y)属于类别$c_i$的概率。

 $\bold{w}$为向量，$\bold{w}=(w_0, w_1, ... , w_n)$ ，由于各特征相互独立, $p(\bold{w}|c_i) = p(w_0, w_1, ..., w_n | c_i) = p(w_0 |c_i)p(w_1|c_i)...p(w_n|c_i)$ 。

## 朴素贝叶斯的假设

+ 特征之间相互独立，且各特征同等重要(naive朴素，常常不成立)

## 准备数据

```python
def loadDataSet():
	postingList=[['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
				 ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
				 ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'him'],
				 ['stop', 'posting', 'stupid', 'worthless', 'garbage'],
				 ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
				 ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
	classVec = [0,1,0,1,0,1] # 1 代表侮辱性的言论, 0 代表正常言论
	return postingList,classVec

def createVocabularyList(dataSet): # 创建一个包含在所有文档中出现的不重复词的列表
	vocabularySet = set({})
	for document in dataSet:
		vocabularySet = vocabularySet | set(document)
	return list(vocabularySet)

def setOfWords2Vec(vocabularyList, inputSet):
	returnVec = [0]*len(vocabularyList)
	for word in inputSet:
		if word in vocabularyList:
			returnVec[vocabularyList.index(word)] = 1
		else:
			print "the word: %s is not in my Vocabulary" % word
	return returnVec

```

## 训练算法

```python
def trainNaiveBayes(trainMatrix, trainCategory):
	numTrainDocs = len(trainMatrix)
	numWords = len(trainMatrix[0])
	pAbusive = sum(trainCategory)/float(numTrainDocs) # 侮辱性言论的总概率
	p0Num = np.zeros(numWords) 
	p1Num = np.zeros(numWords)
	p0Denom = 0.0
	p1Denom = 0.0

	for i in range(numTrainDocs):
		if trainCategory[i] == 1: # 是侮辱性言论
			p1Num += trainMatrix[i]
			p1Denom += sum(trainMatrix[i])
		else:
			p0Num += trainMatrix[i]
			p0Denom += sum(trainMatrix[i])
	p1Vector = p1Num/p1Denom
	p0Vector = p0Num/p0Denom

	return p0Vector, p1Vector, pAbusive

```

`p0Vector`和`p1Vector`和`pAbusive`分别表示$p(w_i|c_0)$和$p(w_i|c_1)$和$p(c_1)$

**改进后**

```python
def trainNaiveBayes(trainMatrix, trainCategory):
	numTrainDocs = len(trainMatrix)
	numWords = len(trainMatrix[0])
	pAbusive = sum(trainCategory)/float(numTrainDocs) # 侮辱性言论的总概率
	p0Num = np.ones(numWords) 
	p1Num = np.ones(numWords)
	p0Denom = 2.0
	p1Denom = 2.0

	for i in range(numTrainDocs):
		if trainCategory[i] == 1: # 是侮辱性言论
			p1Num += trainMatrix[i]
			p1Denom += sum(trainMatrix[i])
		else:
			p0Num += trainMatrix[i]
			p0Denom += sum(trainMatrix[i])
	p1Vector = np.log(p1Num/p1Denom)
	p0Vector = np.log(p0Num/p0Denom)

	return p0Vector, p1Vector, pAbusive
```

## 分类

```python
def classifyNaiveBayes(vec2Classify, p0Vector, p1Vector, pClass1):
	p1 = sum(vec2Classify * p1Vector) + np.log(pClass1) # *为点乘
	p0 = sum(vec2Classify * p0Vector) + np.log(1.0 - pClass1)
	if p1 > p0:
		return 1
	else:
		return 0
```

## 测试

```python
def testingNaiveBayes():
	postingList, classList = loadDataSet()
	myVocabularyList = createVocabularyList(postingList)
	trainMat = []
	for postingDoc in postingList:
		trainMat.append(setOfWords2Vec(myVocabularyList,postingDoc))
	p0V, p1V, pAb = trainNaiveBayes(trainMat, classList)
	testEntry = ['love','my','daimation']
	thisDoc = np.array(setOfWords2Vec(myVocabularyList, testEntry))
	print testEntry, 'classifed as: ', classifyNaiveBayes(thisDoc,p0V,p1V,pAb)
	testEntry = ['stupid','garbage']
	thisDoc = np.array(setOfWords2Vec(myVocabularyList, testEntry))
	print testEntry, 'classied as: ', classifyNaiveBayes(thisDoc,p0V,p1V,pAb)

```

## 朴素贝叶斯词袋模型

上述的`setOfWords2Vec`可以被描述为**词集模型(set of words model)**。如果一个单词在文档中出现不止一次，这意味着包含该词是否出现在文档中所不能表达的某种信息，这种方法称为**词袋模型**。在词袋中，每个单词可以出现多次，而在词集中，每个词只能出现一次。

```python
def bagOfWords2Vec(vocabularyList, inputSet):
    returnVec = [0]*len(vocabularyList)
    for word in inputSet:
        if word in vocabularyList:
            returnVec[vocabularyList.index(word)]+=1
	return returnVec
```





