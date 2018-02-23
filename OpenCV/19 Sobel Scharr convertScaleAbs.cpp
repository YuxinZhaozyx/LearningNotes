#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	imshow("src", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0); // Sobel易受噪声干扰，先模糊减低噪声
	
	Mat graySrc;
	cvtColor(src, graySrc, COLOR_BGR2GRAY);

	Mat xDst, yDst;
	//Sobel函数能用Sobel算子进行卷积操作，获得边缘
	//Sobel算子为一阶算子
	//使用CV_16S以防止计算超过CV_8U范围
	//求导x方向
	//Sobel(graySrc, xDst, CV_16S, 1, 0, 3); // 1为x方向求导阶数，0为y方向求导阶数，3为算子大小
	//求导y方向
	//Sobel(graySrc, yDst, CV_16S, 0, 1, 3); 

	//Sobel函数当ksize==3时计算存在一定误差，Scharr函数是对该缺点的改进
	Scharr(graySrc, xDst, CV_16S, 1, 0); // Scharr不需要ksize，ksize固定为3
	Scharr(graySrc, yDst, CV_16S, 0, 1);

	//对结果取绝对值以防止像素值小于0
	convertScaleAbs(xDst, xDst);
	convertScaleAbs(yDst, yDst);

	//得到整体近似梯度
	//梯度=sqrt(xDst*xDst+yDst*yDst)
	//近似梯度=abs(xDst)+abs(yDst)
	Mat dst = xDst + yDst;

	imshow("xDst", xDst);
	imshow("yDst", yDst);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}