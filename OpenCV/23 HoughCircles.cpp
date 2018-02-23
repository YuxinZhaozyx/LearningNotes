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

	medianBlur(src, src, 3); // 中值滤波减少噪点

	Mat graySrc;
	cvtColor(src, graySrc, COLOR_BGR2GRAY);
	imshow("gray", graySrc);

	Canny(graySrc, graySrc, 100, 200); // 边缘检测
	imshow("canny", graySrc);

	// 霍夫圆检测
	vector<Vec3f> circles;
	HoughCircles(graySrc, circles,
		HOUGH_GRADIENT, // 按梯度找
		1, // dp=1
		10, // 可以分辨两个圆是否是同心圆的最短距离
		200, // canny edges detection high threshold
		60, // 中心点累加器阈值，高于该值判断为圆
		10, // 最小半径
		90  // 最大半径
	);

	Mat dst;
	src.copyTo(dst);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3f cir = circles[i];
		circle(dst, Point(cir[0], cir[1]), cir[2], Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("dst", dst);

	waitKey(0);
	return 0;
}