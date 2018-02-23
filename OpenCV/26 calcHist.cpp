#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/circles.jpg");
	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	Mat dst;
	int channels[][1] = { {0},{1},{2} };
	Mat bHist, gHist, rHist;
	int histSize = 256;
	float range[] = { 0,256 }; //[0,256)
	const float* histRange = { range };

	calcHist(&src, 1, channels[0], Mat(), bHist, 1, &histSize, &histRange, true, false);
	calcHist(&src, 1, channels[1], Mat(), gHist, 1, &histSize, &histRange, true, false);
	calcHist(&src, 1, channels[2], Mat(), rHist, 1, &histSize, &histRange, true, false);
	/*
		&src : arrays 图像的数组，可有多张图像
		1	 ：narrays 图像的数量
		channels[0] : channels 要计算直方图的通道，如有两张图像，第一张通道为{0,1,2},第二张为{0},则 int channels[] = {3,0,2}分别表示第二张图像的0通道和第一张图像的0,2通道
					  若为NULL，则默认一张图片的第0个通道(要求该图片只有一个通道)
		Mat() : mask
		bHist : 输出的直方图，类型为Mat，CV_32F
		1     ：dims 输出的直方图的维数
		&histSize ：图像的大小
		&histRange ： 对[0,256)内的值进行统计
		true ： uniform 是否每个竖条的宽度相同
		false ： accumulate 是否在原输出直方图的基础上累加本次输出直方图，若为false表示先清空原输出直方图的内容再加入本次输出直方图
	*/


	int subWidth = 3;
	int cols = histSize * subWidth;
	int rows = 400;
	Mat histImg = Mat(rows, cols, CV_8UC3, Scalar(0, 0, 0));
	
	normalize(bHist, bHist, 0, rows, NORM_MINMAX);
	normalize(gHist, gHist, 0, rows, NORM_MINMAX);
	normalize(rHist, rHist, 0, rows, NORM_MINMAX);

	for (int i = 1; i < 256; i++)
	{
		line(histImg, Point(subWidth*(i - 1), rows - (int)(bHist.at<float>(i - 1))), Point(subWidth*i, rows - (int)(bHist.at<float>(i))), Scalar(255, 0, 0));
		line(histImg, Point(subWidth*(i - 1), rows - (int)(gHist.at<float>(i - 1))), Point(subWidth*i, rows - (int)(gHist.at<float>(i))), Scalar(0, 255, 0));
		line(histImg, Point(subWidth*(i - 1), rows - (int)(rHist.at<float>(i - 1))), Point(subWidth*i, rows - (int)(rHist.at<float>(i))), Scalar(0, 0, 255));
	}
	
	imshow("dst", histImg);




	waitKey(0);
	return 0;
}