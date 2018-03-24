#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

void DrawSomething(Mat& img,Mat& mask)
{
	vector<Point> Points = {
		Point(80,440),Point(150,330),Point(190,540),Point(143,290),Point(234,250)
	};
	
	for (int i = 0; i < Points.size(); i++)
	{
		line(img, Points[i], Points[(i + 1) % Points.size()], Scalar::all(255), 8);
		line(mask, Points[i], Points[(i + 1) % Points.size()], Scalar::all(255), 8);
	}

}

int main()
{
	Mat src = imread("f:/tempFiles/003.jpg");
	if (src.empty())
		return -1;
	imshow("src", src);
	
	Mat mask(src.size(),CV_8UC1,Scalar::all(0));
	DrawSomething(src, mask);
	imshow("drawed", src);

	Mat dst;
	// src为待修复的原图，mask为修复模板
	inpaint(src, mask, dst, 3, INPAINT_NS); //修复图像，3为选取领域的半径，使用基于Navier-Stokes的方法
	imshow("inpaint NS", dst);

	inpaint(src, mask, dst, 3, INPAINT_TELEA); //修复图像，3为选取领域的半径，使用基于快速行进（FMM）的修复算法
	imshow("inpaint TELEA", dst);

	waitKey(0);
	return 0;
}