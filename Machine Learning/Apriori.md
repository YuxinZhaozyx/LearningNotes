# 使用Apriori算法进行关联分析

+ **优点**：易编码实现
+ **缺点**：在大数据集上可能较慢
+ **适用数据类型**：数值型或标称型

从大规模数据集中寻找物品间的隐含关系被称作关联分析(association analysis)或者关联规则学习(association rule learning)。

## 关联分析

关联分析时一种在大规模数据集中寻找有趣关系的任务。这些关系通常有两种形式：**频繁项集（frequent item set）**或者**关联规则（association rules）**。**频繁项集**是经常出现在一块的物品的集合，**关联规则**暗示两种物品之间可能存在很强的关系。

一个项集的**支持度(support)**：数据集中包含该项集的记录所占比例。

**可信度/置信度(confidence)**：针对一条诸如$ \{A\} \to \{B\} $的关联规则来定义。可信度为
$$
confidence(A,B) =\frac{support(\{A,B\}) } {support(\{A\}) }
$$

**Apriori原理**： 如果某个项集是频繁的，则它的所有子集也是频繁的。

利用它的逆反命题”如果某个项集是非频繁集，则它的所有超级也是非频繁的“可以减少计算量。

### 发现频繁项集

扫描记录查看哪些项集满足最小支持度要求，不满足的集合被去除，然后对剩下的集合进行组合生成包含两个元素的项集。重复此过程直到所有项集都被去除。

```python

def loadDataSet():
	return [[1,3,4],[2,3,5],[1,2,3,5],[2,5]]

def createC1(dataList): # 创建只包含最小元素的集合
	C1 = []
	for record in dataList:
		for item in record:
			if not [item] in C1:
				C1.append([item])
	C1.sort()
	return map(frozenset, C1) # 对C1中每个项构建一个不变集合

def scan(D, Ck, minSupport):
	ssCnt = {}
	for tid in D:
		for can in Ck:
			if can.issubset(tid):
				if not ssCnt.has_key(can): 
					ssCnt[can] = 1
				else:
					ssCnt[can] += 1
	numItems = float(len(D))
	retList = []
	supportData = {}
	for key in ssCnt:
		support = ssCnt[key]/numItems
		if support >= minSupport:
			retList.insert(0,key)
		supportData[key] = support
	return retList, supportData

```

### 组织完整的Apriori算法

```python
def aprioriGen(Lk, k): #创建Ck
	retList = []
	lenLk = len(Lk)
	for i in range(lenLk):
		for j in range(i+1, lenLk):
			L1 = list(Lk[i])[:k-2]
			L2 = list(Lk[j])[:k-2]
			L1.sort()
			L2.sort()
			if L1 == L2:
				retList.append(Lk[i] | Lk[j])
	return retList

def apriori(dataList, minSupport = 0.5):
	C1 = createC1(dataList)
	D = map(set, dataList)
	L1, supportData = scan(D, C1, minSupport)
	L = [L1]
	k = 2
	while len(L[k-2])>0 :
		Ck = aprioriGen(L[k-2],k)
		Lk, supportK = scan(D, Ck, minSupport)
		supportData.update(supportK)
		L.append(Lk)
		k += 1
	return L, supportData
```

### 从频繁项集中挖掘关联规则

```python
def generateRules(L, supportData, minConfidence=0.7):
	bigRuleList = []
	for i in range(1, len(L)):
		for freqSet in L[i]:
			H = [frozenset([item]) for item in freqSet]
			if i>1 :
				rulesFromConfidenceSequence(freqSet, H, supportData, bigRuleList, minConfidence)
			else:
				calcConfidence(freqSet, H, supportData, bigRuleList, minConfidence)
	return bigRuleList

def calcConfidence(freqSet, H, supportData, bigRuleList, minConfidence=0.7):
	prunedH = []
	for conseq in H:
		confidence = supportData[freqSet]/supportData[freqSet-conseq]
		if confidence >= minConfidence:
			print freqSet-conseq, '-->', conseq, 'confidence:', confidence
			bigRuleList.append((freqSet-conseq, conseq, confidence))
			prunedH.append(conseq)
	return prunedH

def rulesFromConfidenceSequence(freqSet, H, supportData, bigRuleList, minConfidence=0.7):
	m = len(H[0])
	if len(freqSet)>m+1 : # 尝试进一步合并
		Hmpl =aprioriGen(H, m+1)
		Hmpl =calcConfidence(freqSet, Hmpl, supportData, bigRuleList, minConfidence)
		if len(Hmpl)>1 : # 创建 Hm+1条新候选规则
			rulesFromConfidenceSequence(freqSet, Hmpl, supportData, bigRuleList, minConfidence)

```

```python
dataList = loadDataSet()
L, supportData = apriori(dataList, 0.5)
bigRuleList = generateRules(L, supportData)
```

