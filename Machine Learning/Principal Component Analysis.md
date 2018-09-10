# 主成分分析(Principal Component Analysis, PCA)

+ **优点**：降低数据的复杂度，识别最重要的多个特征
+ **缺点**：不一定需要，且可能损失有用信息
+ **适用数据类型**： 数值型数据

**伪代码**：

```
Remove the mean
Compute the covariance matrix
Find the eigenvalues and eigenvectors of the covariance matrix
Sort the eigenvalues from largest to smallest
Take the top N eigenvectors
Transform the data into the new space created by the top N eigenvectors
```

**实现**：

```python
import numpy as np 

def loadDataSet(fileName, delim='\t'):
	fr = open(fileName)
	stringArr = [line.strip().split(delim) for line in fr.readlines()]
	dataArr = [map(float, line) for line in stringArr]
	return np.mat(dataArr)

def PCA(dataMat, topNfeat=9999999):
	meanVals = np.mean(dataMat, axis=0)
	meanRemoved = dataMat - meanVals # 去平均值
	covMat = np.cov(meanRemoved, rowvar=0) # 计算协方差矩阵
	eigVals, eigVectors = np.linalg.eig(covMat) # 特征值分析
	eigvalIndex = np.argsort(eigVals) #由小到大排列得到索引
	eigvalIndex = eigvalIndex[:-(topNfeat+1):-1] #反序得到特征值最大的几个
	reducedEigVectors =  eigVectors[:, eigvalIndex] #得到消减后的特征向量
	lowDDataMat = meanRemoved * reducedEigVectors # 将数据转到低维空间
	reconMat = (lowDDataMat * reducedEigVectors.T) + meanVals # 通过降维后的数据重构出新的原数据
	return lowDDataMat, reconMat
```

