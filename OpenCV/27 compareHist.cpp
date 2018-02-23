#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

int main()
{
	Mat src1 = imread("F:/image/00.jpeg");
	Mat src2 = imread("F:/image/002xn1.png");

	if (src1.empty()||src2.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	
	Mat temp1, temp2;
	cvtColor(src1, temp1, COLOR_BGR2HSV);
	cvtColor(src2, temp2, COLOR_BGR2HSV);

	MatND dst1, dst2; //多维矩阵
	int channels[] = { 0,1 };
	int histSize[] = { 180,256 };
	float range[][2] = { {0,180} ,{0,256} };
	const float* histRange[] = { range[0],range[1] };

	calcHist(&temp1, 1, channels, Mat(), dst1, 2, histSize, histRange, true, false);
	calcHist(&temp2, 1, channels, Mat(), dst2, 2, histSize, histRange, true, false);

	normalize(dst1, dst1,0, 256, NORM_MINMAX);
	normalize(dst2, dst2, 0, 256, NORM_MINMAX);


	double bha = compareHist(dst1, dst2, CV_COMP_BHATTACHARYYA); // 巴氏距离，[0,1],越接近0越相似
	double chi = compareHist(dst1, dst2, CV_COMP_CHISQR); // 卡方计算，[0,+INF),越接近0越相似
	double cor = compareHist(dst1, dst2, CV_COMP_CORREL); // 相关性计算，[0,1],越接近1越相似

	cout << "bha = " << bha << endl;
	cout << "chi = " << chi << endl;
	cout << "cor = " << cor << endl;

	imshow("src1", src1);
	imshow("src2", src2);
	waitKey(0);
	return 0;
}