#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("f:/image/00.jpeg");
	if (src.empty())
	{
		return -1;
	}
	imshow("src", src);
	//cvtColor(src, src, COLOR_BGR2GRAY);

	Mat dst(src.size(), src.type());
	
	// 初始图像的四个点
	vector<Point2f> origin(4);
	origin[0].x = 0;
	origin[0].y = 0;
	origin[1].x = 0;
	origin[1].y = src.rows-1;
	origin[2].x = src.cols-1;
	origin[2].y = src.rows-1;
	origin[3].x = src.cols - 1;
	origin[3].y = 0;

	// 最终图像对应于初始图像四个点的四个点
	// 点的排列顺序无关，只需保证相映射的点索引相同
	vector<Point2f> target(4);
	target[0].x = dst.cols * 0.1;
	target[0].y = dst.rows * 0.1;
	target[1].x = dst.cols * 0.3;
	target[1].y = dst.rows * 0.6;
	target[2].x = dst.cols * 0.9;
	target[2].y = dst.rows * 0.9;
	target[3].x = dst.cols * 0.6;
	target[3].y = dst.rows * 0.3;
	
	// 获得变换矩阵(3*3)，可用findHomography或getPerspectiveTransform获得
	Mat warpMat;
	warpMat = findHomography(origin,target);
	//warpMat = getPerspectiveTransform(origin, target);
	
	// 密集透视变换
	warpPerspective(src, dst, warpMat, src.size());

	imshow("dst", dst);

	waitKey(0);
	return 0;
}