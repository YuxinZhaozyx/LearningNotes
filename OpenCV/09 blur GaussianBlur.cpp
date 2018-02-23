#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int args, char* argv[])
{
	Mat src1 = imread("F:/image/64547063_p0.jpg");
	Mat src2 = imread("F:/image/64547063_p1.jpg");
	if (src1.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}
	if (src2.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}

	Mat dst1, dst2;
	blur(src1, dst1, Size(13, 13), Point(-1, -1));//均值模糊，Size(3,3)为掩膜大小，为正奇数，Point(-1,-1)指明以掩膜中心点为中心
	GaussianBlur(src2, dst2, Size(13, 13), 11, 11);//高斯模糊，Size(3,3)为掩膜大小，两个11分别为sigmundX和sigmundY(详见高斯分布公式）
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey(0);

	return 0;
}