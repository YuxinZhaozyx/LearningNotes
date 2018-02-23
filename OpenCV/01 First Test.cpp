#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
int main(int args, char* argv[])
{
	Mat src = imread("F:/ͼƬ/Guilty_Crown10.jpg");
	if (src.empty())
	{
		cerr << "Not Find Picture\n";
		return -1;
	}
	namedWindow("test1", CV_WINDOW_AUTOSIZE);
	imshow("test1", src);
	waitKey(0);
	return 0;
}
