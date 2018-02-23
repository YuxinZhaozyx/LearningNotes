#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int args, char* argv[])
{
	Mat src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	int row = 0, col = 1;
	Vec3b pix = src.at<Vec3b>(row, col); //获取像素点,对于RGB用Vec3b，灰度用uchar
	int b = pix[0];//blue
	int g = pix[1];//green
	int r = pix[2];//red
	src.at<Vec3b>(row, col)[0] = 255 - b;//修改像素点
	src.at<Vec3b>(row, col)[1] = 255 - g;
	src.at<Vec3b>(row, col)[2] = 255 - r;

	Mat dst;
	bitwise_not(src, dst);//对src的每一个像素进行逻辑非操作后保存在dst
	src.convertTo(dst, CV_32FC3); //将CV_8UC3的src转化成CV_32FC3的图像保存在dst中，相当于将src的每一个byte类型值变成float类型值
	//namedWindow("output", CV_WINDOW_AUTOSIZE);
	//imshow("output", dst);

	waitKey(0);

	return 0;
}