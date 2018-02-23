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
	imshow("src", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0); // 降噪
	
	Mat graySrc;
	cvtColor(src, graySrc, COLOR_BGR2GRAY);

	Mat dst;
	//Laplace算子(拉普拉斯算子)，二阶算子
	Laplacian(graySrc, dst, CV_16S, 3);
	convertScaleAbs(dst, dst);

	imshow("dst", dst);
	waitKey(0);
	return 0;
}