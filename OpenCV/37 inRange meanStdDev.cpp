#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("f:/tempFiles/water_coins.jpg");
	if (src.empty())
	{
		return -1;
	}
	imshow("src", src);

	Mat dst;
	inRange(src, Scalar(40, 50, 60), Scalar(200, 200, 200), dst); // 像素值在两种颜色之间的像素将被置为255，不在区间内将被置为0,返回单通道图像; 可用用于单通道或其他颜色空间
	imshow("dst1", dst);

	Mat hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 0, 0), Scalar(30, 255, 255), dst); // 在hsv颜色空间中要识别颜色只需关注第一个通道,可提取出在该颜色范围内的区域
	imshow("dst2", dst);

	Scalar mean, stdDev;
	meanStdDev(src, mean, stdDev); // 计算均值mean和标准差stdDev；各通道的结果储存在各个val[]中
	cout << "mean:\n" << mean.val[0] << " " << mean.val[1] << " " << mean.val[2] << endl;
	cout << "stdDev:\n" << stdDev.val[0] << " " << stdDev.val[1] << " " << stdDev.val[2] << endl;

	waitKey(0);
	return 0;
}