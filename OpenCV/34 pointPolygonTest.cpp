#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<cmath>

using namespace std;
using namespace cv;

int main()
{
	int r = 400;

	Mat src = Mat::zeros(r, r, CV_8UC1);
	
	vector<Point> contour = {
		Point(0.2*r,0.5*r),
		Point(0.7*r,0.2*r),
		Point(0.7*r,0.8*r)
	};

	for (int i = 0; i < contour.size(); i++)
	{
		line(src, contour[i], contour[(i + 1) % contour.size()], Scalar(255, 255, 255));
	}
	imshow("src", src);

	Mat dst = Mat(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			dst.at<float>(i, j) = pointPolygonTest(contour, Point2f(j, i), true); // 点多边形测试，当最后一个参数为false时，返回点与轮廓的位置关系(1在内部，0在边界，-1在外部)，当为true时返回点到多边形的距离(内部>0,外部<0)
		}
	}

	double maxValue;
	double minValue;
	Point maxLoc;
	Point minLoc;
	minMaxLoc(dst, &minValue, &maxValue, &minLoc, &maxLoc, Mat());

	Mat dst_normal;
	dst.copySize(dst_normal);
	normalize(dst, dst_normal, 0, 255, NORM_MINMAX);
	
	Mat img = Mat(src.size(), CV_8UC3);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (dst.at<float>(i, j) < 0)
			{
				float pixel = dst_normal.at<float>(i, j);
				img.at<Vec3b>(i, j) = Vec3b((uchar)pixel, 255 - (uchar)pixel, 0);
			}
			else
			{
				float pixel = dst_normal.at<float>(i, j);
				img.at<Vec3b>(i, j) = Vec3b(0, 255 - (uchar)pixel, (uchar)pixel);
			}
		}
	}
	imshow("img", img);

	waitKey(0);
	return 0;
}