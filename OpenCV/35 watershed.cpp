#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("F:/tempFiles/water_coins.jpg");
	if (src.empty())
	{
		cout << "Not find files";
		return -1;
	}
	imshow("src", src);
	Mat src_;
	src.copyTo(src_);

	Mat gray;
	GaussianBlur(src, src, Size(3,3), 0, 0);
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray0",gray);

	// 增强对比度
	Mat kernel = (Mat_<int>(3, 3) << -1,-1,-1,-1,9,-1,-1,-1,-1);
	filter2D(gray, gray, -1, kernel);
	imshow("gray", gray);

	// 获取mask
	Mat mask;
	threshold(gray, mask, 127, 255, THRESH_BINARY_INV | THRESH_OTSU); // 自适应二值化
	//imshow("mask1",mask);
	
	// 距离变换找到物体
	Mat distImg;
	distanceTransform(mask, distImg, DIST_L1, 3, 5);
	normalize(distImg, distImg, 0, 1, NORM_MINMAX);
	imshow("distImg1", distImg); // CV_32F显示[0,1]内的值

	threshold(distImg, distImg, 0.6, 1.0, THRESH_BINARY);
	imshow("distImg2", distImg);
	
	erode(distImg, distImg, Mat::ones(3, 3, CV_8UC1)); // 腐蚀

	// 得到mask，用于储存标记
	Mat dist8UC1;
	distImg.convertTo(dist8UC1, CV_8UC1, 255);
	vector<vector<Point> > contour;
	findContours(dist8UC1, contour, RETR_TREE, CHAIN_APPROX_SIMPLE);
	mask = Mat::zeros(mask.size(), CV_32SC1); // 转化到CV_32SC1(watershed只能用该类型作为mask)，用于储存标记
	for (size_t i = 0; i < contour.size(); i++)
	{
		drawContours(mask, contour, i, Scalar(i + 2), 1); // 每个标记相差1
	}
	circle(mask, Point(0,0), 3, Scalar(1));
	circle(mask, Point(0, src.rows), 3, Scalar(1));
	
	Mat temp;
	watershed(src_, mask);
	
	temp =Mat(src.size(), src.type(),Scalar(0,0,0));
	for(size_t i=0;i<src.rows;i++)
		for (size_t j = 0; j < src.cols; j++)
		{
			if (mask.at<int>(i, j) >1)
				temp.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
		}
	imshow("temp1", temp);

	vector<Vec3b> color(contour.size()+3);
	for (size_t i = 0; i < color.size(); i++)
		color[i] = Vec3b(i % 255, (73 * (i + 7) % 255), (43 * i + 3) % 255);

	temp = Mat(temp.size(), src.type(), Scalar(0, 0, 0));
	for(size_t i=0;i<src.rows;i++)
		for (size_t j = 0; j < src.cols; j++)
		{
			if (mask.at<int>(i, j) > 1)
			{
				temp.at<Vec3b>(i, j) = color[mask.at<int>(i,j)-2];
			}
			else if (mask.at<int>(i, j) < 0)
			{
				temp.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
		}
	imshow("temp2", temp);

	waitKey(0);
	return 0;
}