#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("f:/tempFiles/timg2.jpg");
	if (src.empty())
		return -1;
	imshow("src", src);

	Mat gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY);

	Mat cornerStrength;
	cornerHarris(gray, cornerStrength, 3, 3, 0.01); // 检测角点 ，获得cornerStrength为浮点型
	threshold(cornerStrength, cornerStrength, 0.001, 255, THRESH_BINARY);

	imshow("harris", cornerStrength);

	waitKey(0);
	return 0;
}