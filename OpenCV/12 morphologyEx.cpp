#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src;
Mat dst;


int main(int args, char* argv[])
{
	src = imread("F:/tempFiles/01.jpg", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	bitwise_not(src, src);

	namedWindow("Input", CV_WINDOW_AUTOSIZE);
	imshow("Input", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//形态学操作
	//morphologyEx(src, dst, MORPH_OPEN, kernel);//开操作，先腐蚀后膨胀，去除小物体
	//morphologyEx(src, dst, MORPH_CLOSE, kernel);//闭操作，先膨胀后腐蚀，去除洞
	//morphologyEx(src, dst, MORPH_TOPHAT, kernel);//顶帽操作，原图-开操作，得到开操作去除的小物体
	//morphologyEx(src, dst, MORPH_BLACKHAT, kernel);//黑帽操作，闭操作-原图，得到闭操作去除的洞
	morphologyEx(src, dst, MORPH_GRADIENT, kernel);//形态学梯度操作，膨胀-腐蚀，保留轮廓
	imshow("Ouput", dst);



	waitKey(0);

	return 0;
}
