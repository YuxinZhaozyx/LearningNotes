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

	Mat result;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
	morphologyEx(binImg, result, MORPH_OPEN, kernel);

	imshow("result", result);


	waitKey(0);

	return 0;
}
