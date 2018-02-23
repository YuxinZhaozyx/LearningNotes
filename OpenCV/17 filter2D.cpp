#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/12.jpg",IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}

	Mat kernel; // 掩膜/算子/卷积核

	// Robert算子
	kernel = (Mat_<int>(2, 2) << 1, 0, 0, -1); // 第一种
	kernel = (Mat_<int>(2, 2) << 0, 1, -1, 0); // 第二种

	// Sobel算子
	kernel = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1); // 第一种
	kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1); // 第二种

	// 拉普拉斯算子
	kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);

	Mat dst;
	filter2D(src, dst, -1, kernel, Point(-1, -1));

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}