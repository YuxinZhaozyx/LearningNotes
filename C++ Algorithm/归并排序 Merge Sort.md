# 归并排序 Merge Sort

## C++代码
```
void MergeSort(int unsortArray[], int begin, int end, int tempArray[])
{
	if (end - begin == 1) return;

	int splitPoint = begin + (end - begin) / 2;

	MergeSort(unsortArray, begin, splitPoint, tempArray);
	MergeSort(unsortArray, splitPoint, end, tempArray);

	int x = begin;
	int y = splitPoint;
	int counter = begin;
	
	while (x < splitPoint || y < end)
	{
		if (x < splitPoint && y < end)
			tempArray[counter++] = (unsortArray[x] < unsortArray[y] ? unsortArray[x++] : unsortArray[y++]);
		else if (x < splitPoint)
			tempArray[counter++] = unsortArray[x++];
		else if (y < end)
			tempArray[counter++] = unsortArray[y++];
	}

	for (int i = begin; i < end; i++)
		unsortArray[i] = tempArray[i];
}
```

## 算法步骤
> 划分: 将序列分成元素个数尽量相等的两半
> 递归: 分别对两部分元素进行归并排序
> 合并: 把两个有序表合并成一个
>> 每次把两个序列中最小的元素加以比较，将较小的元素加入新表 
