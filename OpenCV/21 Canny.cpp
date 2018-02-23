#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src;
Mat graySrc;

int low;//低阈值
int high;//高阈值

void Canny_Demo(int pos, void * data);

int main()
{
	src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0); // 降噪

	cvtColor(src, graySrc, COLOR_BGR2GRAY);

	namedWindow("dst", CV_WINDOW_AUTOSIZE);

	createTrackbar("low", "dst", &low, 255, Canny_Demo);
	createTrackbar("high", "dst", &high, 255, Canny_Demo);
	Canny_Demo(0, NULL);
	
	int input;
	while (input = waitKey(50), input != 27);
	return 0;
}

void Canny_Demo(int pos, void * data)
{
	if (high < low) high = low;
	Mat mask;
	Canny(graySrc, mask, low, high, 3, false); //查找边缘，low和high为阈值，3为Sobel算子的大小，false指明使用近似梯度(若用true则表示使用梯度)
	Mat dst;
	
	src.copyTo(dst, mask);
	imshow("dst", dst);
}