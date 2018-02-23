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

	/*
	Mat dst;
	dst = Mat(src.size(), src.type());
	dst = Scalar(177, 0, 255);
	*/

	/*
	Mat dst;
	dst = src.clone();
	*/

	/*
	Mat dst;
	src.copyTo(dst);
	*/

	/*
	Mat dst = Mat(3, 3, CV_8UC3, Scalar(0, 0, 255));
	cout << "dst=\n" << dst << endl;
	*/

	/*
	Mat dst;
	dst.create(src.size(), src.type());
	dst = Scalar(0, 0, 255);
	*/

	/*
	Mat dst = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	*/

	/*
	Mat dst;
	dst = Mat::zeros(src.size(), src.type());
	dst = Mat::eye(src.size(), src.type());
	*/




	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", dst);

	waitKey(0);

	return 0;
}