#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/01.jpg");
	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	GaussianBlur(gray, gray, Size(3, 3), 0, 0);

	Mat cannyDst;
	double thresh = 100;
	Canny(gray, cannyDst, thresh, thresh*2.0, 3, false);

	imshow("cannyDst", cannyDst);

	vector<vector<Point>> contours;
	findContours(cannyDst, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	vector<Moments> moment(contours.size());  // 图像的矩
	for (size_t i = 0; i < contours.size(); i++)
	{
		moment[i] = moments(contours[i], false); // 计算矩
	}

	vector<Point> center(contours.size());
	vector<double> area(contours.size());
	vector<double> length(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		center[i] = Point(moment[i].m10 / moment[i].m00, moment[i].m01 / moment[i].m00); // 得到轮廓中心点位置
		area[i] = contourArea(contours[i], false); // 得到轮廓围成的面积
		length[i] = arcLength(contours[i], false); // 得到轮廓的长度
	}

	RNG rng(123);
	Mat dst;
	src.copyTo(dst);
	for (size_t i = 0; i < contours.size(); i++)
	{
		cout << "(" << center[i].x << "," << center[i].y << ") Area: " << area[i] << " Length: " << length[i] << endl;
		Scalar color(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		circle(dst, center[i], 3, color, 2);
	}
	imshow("dst", dst);

	waitKey(0);
	return 0;
}
