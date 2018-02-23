#include<opencv2/opencv.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int main(int args,char* argv[])
{
	Mat src, dst;
	src = imread("F:/tempFiles/12.jpg");
	if (src.empty())
	{
		cerr << "Not find file\n";
		return -1;
	}

	dst = Mat::zeros(src.size(), src.type());
	int offset = src.channels();

	/*
	int totalRows = src.rows; //rows为行数
	int totalCols = src.cols*src.channels();//cols为列数，channels()为通道数

	for (int row = 1; row < totalRows - 1; row++)
	{
		const uchar* previous = src.ptr<uchar>(row - 1);
		const uchar* current = src.ptr<uchar>(row); //获取第row行的指针
		const uchar* next = src.ptr<uchar>(row + 1);
		uchar* output = dst.ptr<uchar>(row); //用于修改新图像的指针

		for (int col = offset; col <= totalCols - 1 - offset; col++)
		{
			//saturate_cast<uchar>将值限定在[0,255]
			output[col] = saturate_cast<uchar>(5 * current[col] - current[col - offset] - current[col + offset] - previous[col] - next[col]);//提高对比度的公式
		}
	}

	//以下代码相当于以上所有代码
	*/

	double t = getTickCount();
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);//定义掩膜
	filter2D(src, dst, src.depth(), kernel);//将掩膜作用于src后的结果存放在dst中
	double timeconsume = (getTickCount() - t) / getTickFrequency(); // 计算耗时

	printf("Consume time: %.2f\n", timeconsume);

	namedWindow("input picture", CV_WINDOW_AUTOSIZE);
	imshow("input picture", src);

	namedWindow("output picture", CV_WINDOW_AUTOSIZE);
	imshow("output picture", dst);
	
	waitKey(0);
	return 0;
}