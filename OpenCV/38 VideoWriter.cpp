#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include<fstream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap;
	
	cap.open("f:/tempFiles/001.mp4");
	if (!cap.isOpened())
	{
		return -1;
	}

	namedWindow("src");
	namedWindow("gray");

	//string charMap = "#@$%&MNHGFDSAPOIUYTREWQzxcvbnmasyuiop;,.*^~`..       ";
	string charMap = "       .....,,,,,^^^^^^^****zzzzzzzzAAAAAAAAAAAAAAAA";
	int width = 180; // 水平方向字符数目
	int height = 60; // 垂直方向字符数目

	Mat frame; // 每一帧
	cap.set(CV_CAP_PROP_POS_FRAMES, 650); // 移动到第650帧
	
	cap >> frame;
	imshow("src", frame);
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	
	string fileName = "1.txt";
	ofstream videoOut;
	videoOut.open(fileName, ios_base::out | ios_base::trunc);
	if (!videoOut.is_open())
		return -1;
	
	medianBlur(gray, gray, 3);

	int rowsCount = gray.rows / height;
	int colsCount = gray.cols / width;

	for (int row = 0; row < gray.rows; row+=rowsCount)
	{
		for (int col = 0; col < gray.cols; col+=colsCount)
		{
			int pixelValue = gray.at<uchar>(row,col);
			char pixel = charMap[pixelValue*charMap.size() / 256];
			videoOut << pixel;			
		}
		videoOut << '\n';
	}
	
	VideoWriter output;
	output.open("a.avi", CV_FOURCC('D', 'I', 'V', 'X'), 25, Size(gray.cols, gray.rows), false);
	if (!output.isOpened())
		return -1;
	cap.set(CV_CAP_PROP_POS_FRAMES, 0);

	long long totalFrameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
	while (totalFrameCount--)
	{
		Mat frameSub;
		cap >> frameSub;
		cvtColor(frameSub, gray, COLOR_BGR2GRAY);
		output << gray;
	}
	
	videoOut.close();
	
	waitKey(0);
	cap.release();
	output.release();
	return 0;
}