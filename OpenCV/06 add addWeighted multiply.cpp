#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int args, char* argv[])
{
	Mat src1 = imread("F:/image/64547063_p0.jpg");
	Mat src2 = imread("F:/image/64547063_p1.jpg");
	if (src1.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}
	if (src2.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}

	Mat dst;
	double alpha = 0.5;
	addWeighted(src1, alpha, src2, 1.0 - alpha, 0.0, dst);//图像带权值相加
	//dst = src1*alpha + src2*(1 - alpha);
	//add(src1, src2, dst);//图像直接相加
	//dst = src1 + src2;//矩阵加法
	//dst = src1*src2;//矩阵乘法
	//dst = src1.mul(src2);//矩阵元素对乘
	//multiply(src1, src2, dst);//图像相乘,矩阵元素对乘
	imshow("output", dst);
	waitKey(0);

	return 0;
}