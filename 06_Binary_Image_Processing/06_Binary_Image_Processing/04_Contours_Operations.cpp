#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/Contour.png";
	Mat image = imread(imagePath);
	imshow("input", image);
	Mat imageCopy = image.clone();

	Mat imageGray;
	cvtColor(image, imageGray, COLOR_BGR2GRAY);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imageGray, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(imageCopy, contours, -1, Scalar(0, 0, 255), 2, 8);


	for (int i = 0; i < contours.size(); i++) {
		Moments M = moments(contours[i]);
		int x = int(M.m10 / double(M.m00));
		int y = int(M.m01 / double( M.m00));
		double area = contourArea(contours[i]);
		double len = arcLength(contours[i], true);
		// 求出轮廓的面积与周长
		printf("contour index %d, area: %.2f, length : %.2f \n", i, area, len);
		// 中心点
		circle(imageCopy, Point(x, y), 10, Scalar(255, 0, 0), -1);
		// 外接矩形
		Rect box = boundingRect(contours[i]);
		rectangle(imageCopy, box, Scalar(0, 255, 0), 2, 8, 0);
	}

	imageCopy = image.clone();
	RotatedRect rotrect;
	Point2f rect_points[4];
	Mat boxPoints2f, boxPointsCov;
	for (size_t i = 0; i < contours.size(); i++) {
		// 最小外接矩形
		rotrect = minAreaRect(contours[i]);
		boxPoints(rotrect, boxPoints2f);
		boxPoints2f.assignTo(boxPointsCov, CV_32S);
		polylines(imageCopy, boxPointsCov, true, Scalar(0, 255, 255), 2);
	}

	imageCopy = image.clone();
	Point2f center;
	float radius;
	for (size_t i = 0; i < contours.size(); i++) {
		// 外接圆
		minEnclosingCircle(contours[i], center, radius);
		circle(imageCopy, center, radius, Scalar(255, 125, 125), 2);
	}

	imageCopy = image.clone();
	RotatedRect rellipse;
	for (size_t i = 0; i < contours.size(); i++) {
		// 外接椭圆
		if (contours[i].size() < 5)
			continue;
		rellipse = fitEllipse(contours[i]);
		ellipse(imageCopy, rellipse, Scalar(255, 0, 125), 2);
	}
	imshow("contours", imageCopy);
	waitKey(0);
}