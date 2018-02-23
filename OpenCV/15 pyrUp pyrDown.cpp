#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src;
Mat dst;


int main(int args, char* argv[])
{
	src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);

	//高斯金字塔
	Mat upSrc, downSrc;
	pyrUp(src, upSrc, Size(src.cols * 2, src.rows * 2));//上采样，只能*2
	pyrDown(src, downSrc, Size(src.cols / 2, src.rows / 2));//降采样，只能/2
	imshow("upSrc", upSrc);
	imshow("downSrc", downSrc);

	waitKey(0);

	return 0;
}
