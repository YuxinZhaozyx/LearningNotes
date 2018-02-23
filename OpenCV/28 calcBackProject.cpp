#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

Mat src, hsvSrc;

void CallBack(int pos, void * data);

int main()
{
	src = imread("F:/tempFiles/hh.jpg");
	
	if (src.empty())
	{
		cerr << "Not find files.\n";
		return -1;
	}
	imshow("src", src);

	cvtColor(src, hsvSrc, COLOR_BGR2HSV);
	//mixChannels(src, hsvSrc, vector<int>{0,0});
	
	namedWindow("dst",CV_WINDOW_AUTOSIZE);
	int value = 30;
	createTrackbar("histSize", "dst", &value, 180, CallBack);
	CallBack(30, NULL);

	waitKey(0);
	return 0;
}

void CallBack(int pos, void * data)
{
	Mat dst;
	Mat hist;
	float range[] = { 0,180 };
	const float* histRange[] = { range };
	const int nchannel[] = { 0 };

	calcHist(&hsvSrc, 1, nchannel, Mat(), hist, 1, &pos, histRange, true, false);

	cout << hist.dims << endl;

	normalize(hist, hist, 0, 255, NORM_MINMAX);

	calcBackProject(&hsvSrc, 1, nchannel, hist, dst, histRange, 1.0, true);
	
	imshow("dst", dst);

}