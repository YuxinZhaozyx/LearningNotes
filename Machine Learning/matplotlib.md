# matplotlib 绘图

## 散点图

```python
import matplotlib
from matplotlib import pyplot
import numpy as np

dataSet = np.array([[1,2],[2,3],[3,4],[4,5],[5,6]])
fig = pyplot.figure() 
ax = fig.add_subplot(111)
ax.scatter(dataSet[:,0],dataSet[:,1])
fig.show()
```

