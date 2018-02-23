#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src;
Mat dst;


int main(int args, char* argv[])
{
	src = imread("F:/tempFiles/line1.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);
	Mat grayImg,binImg;
	cvtColor(src, grayImg, COLOR_BGR2GRAY);
	imshow("gray", grayImg);

	adaptiveThreshold(~grayImg, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,31, -6);//自适应二值化
	imshow("bin", binImg);

	Mat hLine = getStructuringElement(MORPH_RECT, Size(16, 1));//横向结构
	Mat vLine = getStructuringElement(MORPH_RECT, Size(1, 10));//纵向结构
	Mat hResult,vResult,temp;
	erode(binImg, temp, hLine);
	dilate(temp, hResult, hLine);
	//morphologyEx(binImg, hResult, MORPH_OPEN, hLine);
	morphologyEx(binImg, vResult, MORPH_OPEN, vLine);//提取出纵向线段
	imshow("hLine", hResult);
	imshow("vLine", vResult);

	waitKey(0);

	return 0;
}
