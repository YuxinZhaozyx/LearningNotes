#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

Mat src, gray, dst;
RNG rng(123);

void CallBack(int pos, void * data);

int main()
{
	src = imread("F:/tempFiles/hh.jpg");

	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	

	cvtColor(src, gray, COLOR_BGR2GRAY);
	
	namedWindow("dst");
	int value = 1;
	createTrackbar("threshold", "dst", &value, 112, CallBack);
	CallBack(1, NULL);

	imshow("dst", dst);

	waitKey(0);
	return 0;
}

void CallBack(int pos, void * data)
{
	Canny(gray, dst, pos, pos * 2);
	
	vector<vector<Point> > contour;
	vector<Vec4i> hierarchy;

	findContours(dst, contour, hierarchy,RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	
	Mat contourImg(src.size(), src.type());
	
	vector<vector<Point> > convex(contour.size());
	for (int i = 0; i < contour.size(); i++)
	{
		convexHull(contour[i], convex[i]); // 凸包
	}


	for (int i = 0; i < contour.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(contourImg, convex, i, color, 2, LINE_8, hierarchy, 0, Point(0, 0));
	}
	imshow("dst", contourImg);
}