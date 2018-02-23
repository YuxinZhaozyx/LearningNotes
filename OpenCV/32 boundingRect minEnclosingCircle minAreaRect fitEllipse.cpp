#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

Mat src, gray,bin, dst;
RNG rng(234);

int main()
{
	src = imread("F:/tempFiles/a1.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);
	src.copyTo(dst);

	cvtColor(src, gray, COLOR_BGR2GRAY);

	double thresh = 136;
	threshold(gray, bin, thresh, 255, THRESH_BINARY);

	imshow("bin", bin);
	
	vector<vector<Point>> contour;
	vector<Vec4i> heriachiary;

	findContours(bin, contour, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> contourPoly(contour.size());
	
	for (size_t i = 0; i < contour.size(); i++)
	{
		approxPolyDP(contour[i], contourPoly[i], 5, true); // 简化多边形边数
	}	

	vector<Rect> rects(contour.size());
	for (size_t i = 0; i < contour.size(); i++)
	{
		rects[i] = boundingRect(contourPoly[i]); // 获得包围轮廓的最小正放的矩形
	}

	vector<Point2f> circleCenter(contour.size());
	vector<float> radius(contour.size());
	for (size_t i = 0; i < contour.size(); i++)
	{
		minEnclosingCircle(contourPoly[i], circleCenter[i], radius[i]); //  获得包围轮廓的最小正圆
	}

	vector<RotatedRect> rotatedRect(contour.size());
	for (size_t i = 0; i < contour.size(); i++)
	{
		rotatedRect[i] = minAreaRect(contourPoly[i]); // 获取最小的旋转的圆
	}

	vector<RotatedRect> myEllipse(contour.size());
	for (size_t i = 0; i < contour.size(); i++)
	{
		if(contourPoly[i].size()>=5) // 只有size()>=5，fitEllipse才能得到椭圆
			myEllipse[i] = fitEllipse(contourPoly[i]); // 获取最小的旋转的椭圆
	}

	for (size_t i = 0; i < contour.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//drawContours(dst, contour, i, color, 2, LINE_AA);
		//rectangle(dst, rects[i], color, 2, LINE_AA);
		//circle(dst, circleCenter[i], radius[i], color, 2, LINE_AA);

		Point2f pts[4];
		rotatedRect[i].points(pts);
		for (int i = 0; i < 4; i++)
			line(dst, pts[i], pts[(i + 1) % 4], color, 2, LINE_AA);

		if(contourPoly[i].size()>=5) 
			ellipse(dst, myEllipse[i], color, 2, LINE_AA);
	}

	imshow("dst", dst);
	
	waitKey(0);
	return 0;
}