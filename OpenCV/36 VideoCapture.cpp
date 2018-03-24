#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(CV_CAP_ANY);

	if (!cap.isOpened())
	{
		return -1;
	}

	// cap.set(CV_CAP_PROP_FPS, 10); // 设置FPS

	namedWindow("frame", CV_WINDOW_AUTOSIZE);

	for (;;)
	{
		Mat frame;
		cap >> frame;
		imshow("frame", frame);
		if (waitKey(30) > 0) break;
	}

	waitKey(0);
	return 0;
}