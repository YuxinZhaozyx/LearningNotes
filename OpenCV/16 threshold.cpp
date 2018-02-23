#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void CallBack(int pos, void* data);

int main()
{
	Mat src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find files";
		return -1;
	}

	Mat graySrc;
	cvtColor(src, graySrc, COLOR_BGR2GRAY);
	
	int value = 0;
	
	namedWindow("bin", CV_WINDOW_AUTOSIZE);
	//createTrackbar("thresh", "bin", &value, 255, CallBack, &graySrc);

	imshow("gray", graySrc);
	//CallBack(value, &graySrc);

	Mat binSrc;
	threshold(graySrc, binSrc, 0, 255, THRESH_OTSU | THRESH_BINARY);//根据Otsu算法自动取值进行二值化
	//threshold(graySrc, binSrc, 0, 255, THRESH_TRIANGLE | THRESH_BINARY);//根据Triangle算法自动取值进行二值化
	imshow("bin", binSrc);

	waitKey(0);
	return 0;
}

void CallBack(int pos, void* data)
{
	Mat binSrc;
	//基本阈值操作
	//threshold(*(Mat*)data, binSrc, pos, 255, THRESH_BINARY); //阈值二值化，pos为阈值，超过阈值取最大值，不超过取0
	//threshold(*(Mat*)data, binSrc, pos, 255, THRESH_BINARY_INV);//阈值反二值化，超过阈值取0，不超过取最大值
	//threshold(*(Mat*)data, binSrc, pos, 255, THRESH_TRUNC);//阈值截断，超过阈值则将该值改为阈值
	//threshold(*(Mat*)data, binSrc, pos, 255, THRESH_TOZERO);//阈值取零，不超过阈值则将该值改为0
	threshold(*(Mat*)data, binSrc, pos, 255, THRESH_TOZERO_INV);//阈值反取零，超过阈值则将该值取0
	
	imshow("bin", binSrc);
}