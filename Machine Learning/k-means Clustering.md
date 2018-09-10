# k-均值聚类(k-means Clustering)

+ **优点**： 容易实现
+ **缺点**：可能收敛到局部最小值，在大规模数据集上收敛较慢
+ **适用数据类型**：数值型数据

伪代码：

```
Create k points for starting centroids (often randomly)
While any point has changed cluster assignment
	for every point in our dataset:
		for every centroid
			calculate the distance between the centroid and point
		assign the point to the cluster with the lowest distance
	for every cluster calculate the mean of the points in that cluster
		assign the centroid to the mean
```

**实现**

```python
import numpy as np 

def loadDataSet(fileName):
	dataList = []
	fr = open(fileName)
	for line in fr.readlines():
		curLine = line.strip().split('\t')
		fitLine = map(float, curLine) # 将curLIne中每个元素转为float
		dataList.append(fitLine)
	return dataList

def calcEuclideanDistance(vecA, vecB): # 使用欧式距离，也可用其他距离函数
	return np.sqrt(np.sum(np.power(vecA - vecB, 2)))

def randomCentroids(dataMat, k):
	n = np.shape(dataMat)[1]
	centroids = np.mat(np.zeros((k,n)))
	for j in range(n):
		minJ = np.min(dataMat[:,j])
		maxJ = np.max(dataMat[:,j])
		rangeJ = float(maxJ-minJ)
		centroids[:,j] = minJ + rangeJ * np.random.rand(k,1)
	return centroids

def kMeans(dataMat, k, calcDistance = calcEuclideanDistance, createCentroids = randomCentroids):
	m = np.shape(dataMat)[0]
	clusterAssignment = np.mat(np.zeros((m,2)))
	centroids = createCentroids(dataMat, k)
	clusterChanged = True
	while clusterChanged:
		clusterChanged = False
		for i in range(m):
			minDistance = np.inf
			minIndex = -1
			for j in range(k):
				distance = calcDistance(centroids[j,:], dataMat[i,:])
				if distance < minDistance:
					minDistance = distance
					minIndex = j
			if clusterAssignment[i,0] != minIndex:
				clusterChanged = True
			clusterAssignment[i,:] = minIndex, minDistance**2
		print centroids
		for clusterIndex in range(k):
			pointsInCluster = dataMat[np.nonzero(clusterAssignment[:,0].A == clusterIndex)[0]]
			centroids[clusterIndex, :] = np.mean(pointsInCluster, axis=0)
	return centroids, clusterAssignment


```

## 使用后处理提升聚类性能

一种用于度量聚类效果的指标是SSE(Sum of Squared Error，误差平方和)，对应于`clusterAssigment`中的第一列。

**方法一**：将具有最大SSE值的簇分成两个簇。具体实现时可以将最大簇包含的点过滤出来并在这些点上运行K-means算法，其中k=2

**方法二**：合并最近的两个簇

**方法三**：合并两个使得SSE增幅最小的簇。计算所有所有可能的两个簇合并后的总SSE，找到最佳的两个簇。

## 二分K-均值算法（bisecting k-means）

**伪代码**：

```
Start with all the points in one cluster
While the number of clusters is less than k
	for every cluster
		measure total error
		perform k-means clustering with k=2 on the given cluster
		measure total error after k-means has split the cluster in two
	choose the cluster split that gives the lowest error and commit this split
```

**实现**：

```python
def biKMeans(dataMat, k, calcDistance = calcEuclideanDistance):
	m = np.shape(dataMat)[0]
	clusterAssignment = np.mat(np.zeros((m,2)))
	centroid0 = np.mean(dataMat, axis=0).tolist()[0]
	centroidList = [centroid0]
	for j in range(m):
		clusterAssignment[j,1] = calcDistance(dataMat[j,:], np.mat(centroid0))**2
	while len(centroidList) < k :
		lowestSSE = np.inf
		for i in range(len(centroidList)):
			pointsInCluster = dataMat[np.nonzero(clusterAssignment[:,0].A == i)[0], :]
			centroidMat, splitClusterAssignment = kMeans(pointsInCluster, 2, calcDistance)
			SSESplit = np.sum(splitClusterAssignment[:,1])
			SSENotSplit = np.sum(clusterAssignment[np.nonzero(clusterAssignment[:,0].A != i)[0], 1])
			print "SSESplit, SSENotSplit = ", SSESplit, SSENotSplit
			if SSESplit + SSENotSplit < lowestSSE:
				bestCentroidToSplit = i
				bestNewCentroidMat = centroidMat
				bestClusterAssignment = splitClusterAssignment.copy()
				lowestSSE = SSESplit + SSENotSplit
		
		bestClusterAssignment[np.nonzero(bestClusterAssignment[:,0].A == 0)[0], 0] = bestCentroidToSplit
		bestClusterAssignment[np.nonzero(bestClusterAssignment[:,0].A == 1)[0], 0] = len(centroidList)

		print 'the bestCentroidToSplit is ', bestCentroidToSplit
		print 'the len of bestClusterAssignment is ', len(bestClusterAssignment)
		centroidList[bestCentroidToSplit] = bestNewCentroidMat[0,:].tolist()[0]
		centroidList.append(bestNewCentroidMat[1,:].tolist()[0])
		clusterAssignment[np.nonzero(clusterAssignment[:,0].A == bestCentroidToSplit)[0], :] = bestClusterAssignment

	return np.mat(centroidList), clusterAssignment
```

