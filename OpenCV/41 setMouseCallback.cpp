#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;

cv::Point pbegin(0,0);
cv::Point pend(255, 255);

cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
cv::Mat temp(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

// 定义一个鼠标事件响应函数
static void onMouse(int event, int x, int y, int flag, void* ustc)
{
	/*
	event为事件 
		#define CV_EVENT_MOUSEMOVE 0             //滑动  
		#define CV_EVENT_LBUTTONDOWN 1           //左键点击  
		#define CV_EVENT_RBUTTONDOWN 2           //右键点击  
		#define CV_EVENT_MBUTTONDOWN 3           //中键点击  
		#define CV_EVENT_LBUTTONUP 4             //左键放开  
		#define CV_EVENT_RBUTTONUP 5             //右键放开  
		#define CV_EVENT_MBUTTONUP 6             //中键放开  
		#define CV_EVENT_LBUTTONDBLCLK 7         //左键双击  
		#define CV_EVENT_RBUTTONDBLCLK 8         //右键双击  
		#define CV_EVENT_MBUTTONDBLCLK 9         //中键双击  
	x和y为鼠标位置
	flag为鼠标的拖拽事件，以及键盘鼠标联合事件，共有32种事件
		#define CV_EVENT_FLAG_LBUTTON 1       //左鍵拖曳  
		#define CV_EVENT_FLAG_RBUTTON 2       //右鍵拖曳  
		#define CV_EVENT_FLAG_MBUTTON 4       //中鍵拖曳  
		#define CV_EVENT_FLAG_CTRLKEY 8       //(8~15)按Ctrl不放事件  
		#define CV_EVENT_FLAG_SHIFTKEY 16     //(16~31)按Shift不放事件  
		#define CV_EVENT_FLAG_ALTKEY 32       //(32~39)按Alt不放事件  
	函数指针 void *ustc标识了所响应的事件函数，相当于自定义了一个OnMouseAction()函数的ID。

	*/
	if (event == cv::EVENT_LBUTTONDOWN) 
	{
		pbegin = cv::Point(x, y);
	}
	else if (event==cv::EVENT_MOUSEMOVE && (flag&cv::EVENT_FLAG_LBUTTON))
	{
		pend = cv::Point(x, y);
		img.copyTo(temp);
		cv::rectangle(temp, pbegin, pend, cv::Scalar(255, 255, 255),5);
		imshow("img", temp);
	}
	if (event == cv::EVENT_LBUTTONUP)
	{
		temp.copyTo(img);
	}
}

int main()
{
	

	cv::namedWindow("img"); // 窗口的定义应在setMouseCallback之前
	cv::setMouseCallback("img", onMouse, (void *)0); // 将onMouse设置为"img"窗口的鼠标响应事件,0为鼠标响应处理函数的ID，识别号  
	""
	imshow("img", img);
	cv::waitKey(0);
	return 0;
}