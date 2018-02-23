#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

Mat src, graySrc, dst;

int main()
{
	src = imread("F:/tempFiles/line1.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);

	cvtColor(src, graySrc, COLOR_BGR2GRAY);

	// 查找边缘
	Canny(graySrc, graySrc, 50, 100,3);
	imshow("graySrc", graySrc);

	vector<Vec4f> lines;

	// 查找直线 霍夫直线
	HoughLinesP(graySrc,
		lines, // 输出结果：直线两端的两个点 Vec4f(x1,y1,x2,y2)
		1.0, // 生成极坐标时候的像素扫描的步长
		CV_PI / 180.0, // 生成极坐标时候的查找角度的步长
		10, // 阈值，只有超过多少个点相交在该点才认为是直线
		0, // 最小直线长度(以像素为单位)
		3 // 最大间隔，决定间隔多远之内的直线识别为同一直线
	);

	vector<Vec2f> lines2;
	HoughLines(
		graySrc,
		lines2, // 输出结果:直线的极坐标 Vec2f(θ,r) r=x*cosθ+y*sinθ
		1.0, // 生成极坐标时候的像素扫描的步长
		CV_PI / 180.0, // 生成极坐标时候的查找角度的步长
		10, // 阈值，只有超过多少个点相交在该点才认为是直线
		0, // 当为0时使用经典霍夫直线变换，否则使用多尺度霍夫直线变换
		0, // 当为0时使用经典霍夫直线变换，否则使用多尺度霍夫直线变换
		0, // 最小角度
		CV_PI //最大角度
	);
	
	cvtColor(graySrc, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4f templine = lines[i];
		line(dst, Point(templine[0], templine[1]), Point(templine[2], templine[3]), Scalar(0, 0, 225), 1, LINE_AA);
	}
	
	imshow("dst", dst);
	waitKey(0);

	return 0;
}