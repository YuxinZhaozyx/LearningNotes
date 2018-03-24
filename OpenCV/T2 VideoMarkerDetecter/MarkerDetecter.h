#pragma once
#include<vector>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class MarkerDetecter
{
private:
	Mat m_imageSrc; // source image
	Mat m_imageGray; // gray image
	Mat m_imageBin; // binary image
	vector<Mat> m_imageResult; // result image
	vector<vector<Point> > m_allContours; // all contours got from image
	vector<vector<Point2f> > m_validContours; // valid contours that has 4 vertices and the length of minimal edge of which larger than threshold
	double m_binaryThreshold; // threshold for binary thresholding
	double m_minLengthThreshold; // threshold of the length of minimal edge of contours
	double m_epsilon; // epsilon for approxPolyDP
	int m_thresholdType; // threshold type of binary threshold
	Size m_resultSize; // the size of result image

	void calcGrayImage();
	void calcBinaryImage();
	void calcAllContours();
	void calcValidContours();
	void calcResultImage();
	
public:
	MarkerDetecter(Mat p_imageSrc = Mat(),  Size p_resultSize = Size(100, 100), double p_binaryThreshold = 100, int p_thresholdType = THRESH_OTSU | THRESH_BINARY, double p_minLengthThreshold = 40, double p_epsilon = 10);
	
	void open(Mat p_imageSrc,  Size p_resultSize = Size(100, 100), double p_binaryThreshold = 100, int p_thresholdType = THRESH_OTSU | THRESH_BINARY, double p_minLengthThreshold = 40, double p_epsilon = 10);
	
	void setBinaryThreshold(double p_threshold);
	void setMinLengthThreshold(double p_threshold);
	void setEpsilon(double p_epsilon);
	void setThresholdType(int p_thresholdType);
	void setResultSize(Size p_resultSize);

	void update();
	vector<Mat> getResultImage() const;
	
};

