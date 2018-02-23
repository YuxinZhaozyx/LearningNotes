#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat src;
Mat dst;

void Callback(int, void *);

int main(int args, char* argv[])
{
	src = imread("F:/tempFiles/01.jpg");
	if (src.empty())
	{
		cerr << "Not find files\n";
		return -1;
	}
	int curSize = 3;
	int maxSize = 21;

	namedWindow("Output", CV_WINDOW_AUTOSIZE);
	createTrackbar("Size:", "Output", &curSize, maxSize, Callback,NULL);//创建一个滑条，滑条当前的值保存在curSize中，最大值为maxSize，Callback为调用的函数,NULL为Callback的第二个参数userdata
	Callback(curSize, NULL);//需让窗口显示一次后滑条才有用

	waitKey(0);

	return 0;
}

void Callback(int pos, void * userdata)
{
	int size = pos * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(size, size), Point(-1, -1)); //定义结构元素，MORPH_RECT指定形状
	//erode(src, dst, structureElement, Point(-1, -1), 1);//腐蚀，1为迭代次数
	dilate(src, dst, structureElement, Point(-1, -1), 1);//膨胀
	imshow("Output", dst);
}