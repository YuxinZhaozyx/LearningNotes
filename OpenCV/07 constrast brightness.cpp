#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int args, char* argv[])
{
	Mat src = imread("F:/tempFiles/11.jpg");
	if (src.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}
	imshow("input", src);

	Mat dst;
	dst.create(src.size(), src.type());
	src.convertTo(src, CV_32F);

	double alpha=1.2;//控制对比度
	double beta = 10;//控制亮度

	int totalRows = src.rows;
	int totalCols = src.cols;

	for (int row = 0; row < totalRows; row++)
	{
		for (int col = 0; col < totalCols; col++)
		{
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alpha*src.at<Vec3f>(row, col)[0]+beta);
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*src.at<Vec3f>(row, col)[1]+beta);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*src.at<Vec3f>(row, col)[2]+beta);
		}
	}
	imshow("output", dst);
	waitKey(0);

	return 0;
}