#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include"MarkerDetecter.h"
#include<stdexcept>


using namespace std;
using namespace cv;

void MarkerDetecter::calcGrayImage()
{
	if (m_imageSrc.empty())
		throw runtime_error("Not load source image");

	if (m_imageSrc.channels() == 3) // RGB image
		cvtColor(m_imageSrc, m_imageGray, COLOR_BGR2GRAY);
	else // GRAY image
		m_imageSrc.copyTo(m_imageGray);
}

void MarkerDetecter::calcBinaryImage()
{
	if (m_imageGray.empty())
		throw runtime_error("Not calculate gray image");

	threshold(m_imageGray, m_imageBin, m_binaryThreshold, 255, m_thresholdType);
}

void MarkerDetecter::calcAllContours()
{
	if (m_imageBin.empty())
		throw runtime_error("Not calculate binary image");

	m_allContours.clear();
	findContours(m_imageBin, m_allContours, RETR_LIST, CHAIN_APPROX_SIMPLE);
}

void MarkerDetecter::calcValidContours()
{
	// clear the valid contours list
	m_validContours.clear();
	for (size_t i = 0; i < m_allContours.size(); i++)
	{
		// simplify the contour
		vector<Point2f> approxContour;
		approxPolyDP(m_allContours[i], approxContour, m_epsilon, true); 

		// check the count of vertices
		if (approxContour.size() != 4)
			continue;

		// check the minimal length of edges
		double minLength;
		minLength = min(min(norm(approxContour[0] - approxContour[1]), norm(approxContour[1] - approxContour[2])), min(norm(approxContour[2] - approxContour[3]), norm(approxContour[3] - approxContour[0])));
		if (minLength < m_minLengthThreshold)
			continue;

		// sort vertices to clockwise
		double isClockwise = (approxContour[1] - approxContour[0]).cross(approxContour[3] - approxContour[0]);
		if (isClockwise > 0) // if vertices is ranks as anticlockwise
			swap(approxContour[1], approxContour[3]);

		// add it into m_validContours
		m_validContours.push_back(approxContour);
	}
}

void MarkerDetecter::calcResultImage()
{
	m_imageResult.clear();

	vector<Point2f> target(4);
	target[0] = Point2f(0, 0);
	target[1] = Point2f(m_resultSize.width - 1, 0);
	target[2] = Point2f(m_resultSize.width - 1, m_resultSize.height - 1);
	target[3] = Point2f(0, m_resultSize.height - 1);

	for (size_t i = 0; i < m_validContours.size(); i++)
	{
		Mat warpMat;
		warpMat = getPerspectiveTransform(m_validContours[i], target);

		m_imageResult.push_back(Mat());
		warpPerspective(m_imageSrc, m_imageResult[i], warpMat, m_resultSize);
	}
}
MarkerDetecter::MarkerDetecter(Mat p_imageSrc, Size p_resultSize, double p_binaryThreshold, int p_thresholdType, double p_minLengthThreshold, double p_epsilon)
{
	open(p_imageSrc, p_resultSize, p_binaryThreshold, p_thresholdType, p_minLengthThreshold, p_epsilon);
}

void MarkerDetecter::open(Mat p_imageSrc, Size p_resultSize, double p_binaryThreshold,  int p_thresholdType, double p_minLengthThreshold, double p_epsilon)
{
	p_imageSrc.copyTo(m_imageSrc);
	setBinaryThreshold(p_binaryThreshold);
	setResultSize(p_resultSize);
	setThresholdType(p_thresholdType);
	setMinLengthThreshold(p_minLengthThreshold);
	setEpsilon(p_epsilon);
}

void MarkerDetecter::setBinaryThreshold(double p_threshold)
{
	m_binaryThreshold = p_threshold;
}

void MarkerDetecter::setMinLengthThreshold(double p_threshold)
{
	m_minLengthThreshold = p_threshold;
}

void MarkerDetecter::setEpsilon(double p_epsilon)
{
	m_epsilon = p_epsilon;
}

void MarkerDetecter::setThresholdType(int p_thresholdType)
{
	m_thresholdType = p_thresholdType;
}

void MarkerDetecter::setResultSize(Size p_resultSize)
{
	m_resultSize = p_resultSize;
}

vector<Mat> MarkerDetecter::getResultImage() const
{
	return m_imageResult;
}

void MarkerDetecter::update()
{
	calcGrayImage();
	calcBinaryImage();
	calcAllContours();
	calcValidContours();
	calcResultImage();
}