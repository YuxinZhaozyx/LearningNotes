#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

Mat src,temp;

void CallBack(int pos, void * data);

int main()
{
	src = imread("F:/tempFiles/hh.jpg");

	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	Range rowsRange(150, 300);
	Range colsRange(125, 270);
	
	temp = src(rowsRange, colsRange); // 选取原图像中部分区域作为模板

	imshow("temp", temp);
	
	int value = 0;
	createTrackbar("type", "src", &value, 5, CallBack);
	CallBack(0, NULL);

	
	
	waitKey(0);
	return 0;
}

void CallBack(int pos, void * data)
{
	Mat dst;
	src.copyTo(dst);

	int width = src.cols - temp.cols + 1;
	int height = src.rows - temp.rows + 1;
	Mat result(height, width, CV_32FC1); // 接受结果的矩阵必须为此大小和类型，矩阵的每一个元素储存的是以该点为左上角计算出的结果
	
	matchTemplate(src, temp, result, pos, Mat()); // 匹配模板
	/*
	使用pos来表示类型
		0 : TM_SQDIFF // 平方不同 越小越相似
		1 : TM_SQDIFF_NORMED; // 平方不同 归一化版本
		2 : TM_CCORR; // 相关性 越大越相似
		3 : TM_CCORR_NORMED; // 相关性 归一化版本
		4 : TM_CCOEFF; // 相关系数 越大越相似
		5 : TM_CCOEFF_NORMED; // 相关系数 归一化版本
	*/
	
	//normalize(result, result, 0.0, 1.0, NORM_MINMAX);

	double min, max; // 存放最大值和最小值
	Point minLoc, maxLoc; // 存放最大值和最小值所在像素位置

	minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat()); // 找结果中的最大值和最小值

	Point targetPoint;
	if (pos / 2 == 0) // 平方不同
		targetPoint = minLoc;
	else
		targetPoint = maxLoc;

	Rect targetRect(targetPoint, Point(targetPoint.x + temp.cols, targetPoint.y + temp.rows));
	rectangle(dst, targetRect, Scalar(0, 0, 255), 2, LINE_8);

	imshow("src", dst);
}