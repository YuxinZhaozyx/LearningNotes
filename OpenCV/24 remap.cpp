#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/circles.jpg");
	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	Mat map_x = Mat::zeros(src.size(), CV_32FC1);
	Mat map_y = Mat::zeros(src.size(), CV_32FC1);

	for(int i=0;i<map_x.rows;i++)
		for (int j = 0; j < map_x.cols; j++)
		{
			map_x.at<float>(i, j) = map_x.cols - j;
			map_y.at<float>(i, j) = map_x.rows - i;
		}
	
	Mat dst;
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 225));

	imshow("dst", dst);

	for(int i=0;i<map_x.rows;i++)
		for (int j = 0; j < map_x.cols; j++)
		{
			if (j > 0.25*map_x.cols&&j < 0.75*map_x.cols)
			{
				map_x.at<float>(i, j) = 2 * j - 0.5*map_x.cols;
				map_y.at<float>(i, j) = i;
			}
			else
			{
				map_x.at<float>(i, j) = 0;
				map_y.at<float>(i, j) = 0;
			}
		}
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 225));
	imshow("dst2", dst);

	waitKey(0);
	return 0;
}