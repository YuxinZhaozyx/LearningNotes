#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
int main(int args, char* argv[])
{
	Mat src = imread("F:/ͼƬ/Guilty_Crown10.jpg",IMREAD_COLOR);
	if (src.empty())
	{
		cerr << "Not Find Picture\n";
		return -1;
	}
	namedWindow("test1", CV_WINDOW_FULLSCREEN);//定义窗口
	imshow("test1", src);//显示图片
	
	namedWindow("test2", CV_WINDOW_AUTOSIZE);
	Mat output;
	cvtColor(src, output, CV_BGR2GRAY);//转换颜色空间
	imshow("test2", output);

	imwrite("F:/ͼƬ/Guilty_Crown10_Gray.jpg", output);//保存图片
	
	waitKey(0);
	return 0;
}
