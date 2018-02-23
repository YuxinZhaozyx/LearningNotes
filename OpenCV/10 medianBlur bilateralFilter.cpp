#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int args, char* argv[])
{
	Mat src = imread("F:/tempFiles/11.jpg");
	if (src.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}
	imshow("input", src);

	Mat dst, result;
	//medianBlur(src, dst, 5);//中值模糊，3为掩膜大小3*3,为奇数,取范围内中值
	bilateralFilter(src, dst, 15, 100, 3);//双边模糊，15为空域值，100为确定是否模糊的差值，3只有当15处为负数时才有用，根据该值确定空域值


	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst, result, dst.depth(), kernel);
	imshow("output1", dst);
	imshow("output2", result);
	waitKey(0);

	return 0;
}