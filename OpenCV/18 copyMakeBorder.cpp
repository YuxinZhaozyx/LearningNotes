#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	Mat dst;

	int top, bottom, left, right;
	top = bottom = 0.05*src.rows;
	left = right = 0.05*src.cols;

	Scalar color = Scalar(0, 0, 255);
	copyMakeBorder(src, dst, top, bottom, left, right, BORDER_DEFAULT, color); // 添加边界，BORDER_DEFAULT 镜像边界像素
	copyMakeBorder(src, dst, top, bottom, left, right, BORDER_CONSTANT, color); // 添加边界，BORDER_CONSTANT 将边界用color填充
	copyMakeBorder(src, dst, top, bottom, left, right, BORDER_REFLECT, color); // 添加边界，BORDER_REFLECT 镜像边界像素
	copyMakeBorder(src, dst, top, bottom, left, right, BORDER_WRAP, color); // 添加边界，BORDER_WRAP 平铺图像作为边缘
	copyMakeBorder(src, dst, top, bottom, left, right, BORDER_REPLICATE, color); // 添加边界，BORDER_REPLICATE 延伸边界像素
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}