#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int rows = 720;
int cols = 1280;
Mat bg = Mat::zeros(rows, cols, CV_8UC3);

void MyLine();
void MyRectangle();
void MyCircle();
void MyEllipse();
void MyPolygon();
void RandomRect();
void MyText();

int main(int args, char* argv[])
{
	bg = Scalar(255, 255, 255);
	//MyLine();
	//MyRectangle();
	//MyCircle();
	//MyEllipse();
	//MyPolygon();
	//RandomRect();
	MyText();

	imshow("test", bg);
	waitKey(0);

	return 0;
}

void MyLine()
{
	Point start = Point(50, 20);
	Point end = Point(500, 230);
	Scalar color = Scalar(0, 0, 255);
	line(bg, start, end, color, 3, LINE_8);
}

void MyRectangle()
{
	Point leftUp = Point(60, 30);
	Point rightDown = Point(450, 500);
	Rect box = Rect(leftUp, rightDown);
	Scalar color = Scalar(255, 0, 0);
	rectangle(bg, box, color, 2, LINE_8);
}

void MyCircle()
{
	Point center = Point(bg.cols / 2, bg.rows / 2);
	int radius = 50;
	Scalar color = Scalar(0, 255, 0);
	circle(bg, center, radius, color, 4, LINE_AA);
}

void MyEllipse()
{
	Point center = Point(bg.cols / 2, bg.rows / 2);
	Size size = Size(100, 50);//指定长轴和短轴长
	Scalar color = Scalar(255, 255, 0);
	ellipse(bg, center, size, 0, 0, 360, color, 3, LINE_8); //指定各角度的旋转方向都为顺时针
}

void MyPolygon()
{
	Point points1[1][5] = {
		{Point(250,300),Point(400,250),Point(200,50),Point(100,200),Point(250,300)},
	};
	Point points2[1][4] = {
		{Point(600,300),Point(800,300),Point(900,450),Point(500,400)}
	};//最后一个点没必要与第一个相同

	const Point* pts[] = { points1[0],points2[0] };
	int pointCount[] = { 5 ,4 };
	Scalar color = Scalar(120, 255, 120);
	fillPoly(bg, pts, pointCount, 2, color, LINE_8);

}

void RandomRect()
{
	RNG rng(12345);//设置随机数种子
	
	int T = 10000;
	while (T--)
	{
		//rng.uniform(begin,end)得到[begin,end)内的随机数,模板函数，返回值的类型有输入参数确定，若需要浮点型的随机数，只需将输入参数转换为浮点型
		Rect box = Rect(Point(rng.uniform(0, cols), rng.uniform(0, rows)), Point(rng.uniform(0, cols), rng.uniform(0, rows)));
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		rectangle(bg, box, color, 2, LINE_8);
		if (waitKey(50) > 0)	break; //当已打开了任意一个HighGUI时才有作用，50为等待输入的时间间隔，若在该时间段内接收到输入则返回输入值的ASCII码
		imshow("test", bg);
	}
}

void MyText()
{
	Point start = Point(235, 235);
	Scalar color = Scalar(20, 20, 20);
	char text[] = "hello opencv";
	putText(bg, text, start, CV_FONT_BLACK, 3.0, color, 1, LINE_8);
}