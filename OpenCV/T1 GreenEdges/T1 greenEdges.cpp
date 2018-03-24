#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("f:/image/lugu.jpg");
	if (src.empty())
	{
		return -1;
	}
	
	imshow("src", src);

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	Mat edgeImg;
	double thresh1 = 100;
	Canny(gray, edgeImg, thresh1, thresh1 * 2);
	
	imshow("edge", edgeImg);

	Mat dst;
	src.copyTo(dst);
	uchar thresh2 = 10;
	for(size_t i=0;i<dst.rows;i++)
		for (size_t j = 0; j < dst.cols; j++)
		{
			if (edgeImg.at<uchar>(i, j) >= thresh2)
				dst.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
		}
	imshow("dst", dst);

	waitKey(0);
	return 0;
}