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

	//直方图均衡化能提高对比度

	// 对灰度图像进行直方图均衡化
	Mat graySrc;
	cvtColor(src, graySrc, COLOR_BGR2GRAY);
	imshow("gray", graySrc);
	equalizeHist(graySrc, dst);
	imshow("gray hist", dst);

	// 对彩色图像进行直方图均衡化
	Mat YUVSrc;
	cvtColor(src, YUVSrc, COLOR_BGR2YCrCb); //转成YUV，第一个通道Y为亮度，U和V为色度
	imshow("YUV", YUVSrc);
	vector<Mat> channels;
	split(YUVSrc, channels); //分离各个通道
	equalizeHist(channels[0], channels[0]); //对亮度通道进行直方图均衡化
	merge(channels, dst); //合并各通道
	cvtColor(dst, dst, COLOR_YCrCb2BGR); //转回RGB
	imshow("YUV hist", dst);



	waitKey(0);
	return 0;
}