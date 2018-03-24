#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include"MarkerDetecter.h"

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("f:/tempFiles/00perspective.jpg");
	if (src.empty())
	{
		return -1;
	}
	imshow("src", src);

	/*
	Mat src;
	VideoCapture cap(0);
	for (;;)
	{
		cap >> src;
		if (src.empty())
			return -1;
		imshow("src", src);
		if (waitKey(30) > 0)
			break;
	}
	*/

	MarkerDetecter detecter;
	detecter.open(src,Size(300,300),100,THRESH_OTSU|THRESH_BINARY,40,10);
	detecter.update();
	
	vector<Mat> result;
	result = detecter.getResultImage();

	string output = "dst";
	for (size_t i = 0; i < result.size(); i++)
	{
		imshow(output + char('0'+i), result[i]);
	}
	cout << result.size() << endl;


	waitKey(0);
	return 0;
}