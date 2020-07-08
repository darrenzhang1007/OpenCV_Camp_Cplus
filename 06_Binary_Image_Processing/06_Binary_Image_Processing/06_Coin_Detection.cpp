#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>

using namespace std;
using namespace cv;
void assignment_two();
void assignment_one();


void assignment_one() {
	// Read image
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/CoinsA.png");
	imshow("input", img);

	// Threshold
	Mat imgGray, Binary;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	vector<Mat> mv;
	split(img, mv);
	float t = threshold(mv[1], Binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	imshow("Binary", Binary);

	// 形态学操作
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(Binary, Binary, MORPH_CLOSE, kernel, Point(-1, -1));
	morphologyEx(Binary, Binary, MORPH_OPEN, kernel, Point(-1, -1), 4);
	imshow("Binary1", Binary);

	// 轮廓发现
	vector<Vec4i> hireachy;
	vector<vector<Point>> contours;
	findContours(Binary, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	cout << "硬币个数为: " << contours.size() << endl;
	Mat result = img.clone();
	Point2f center;
	float radius;

	// 绘制轮廓
	for (size_t t = 0; t < contours.size(); t++) {
		minEnclosingCircle(contours[t], center, radius);
		circle(result, center, radius, Scalar(0, 255, 255), 2, 8, 0);
		Moments mm = moments(contours[t]);
		double cx = mm.m10 / mm.m00;
		double cy = mm.m01 / mm.m00;
		circle(result, Point(cx, cy), 2, Scalar(255, 0, 0), 2, 8, 0);
	}
	// 显示结果
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();
}

void assignment_two() {
	// 加载图像
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/CoinsB.png");
	imshow("Original Image", img);

	// 阈值化操作
	Mat gray, binary;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	float t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// 形态学操作
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(binary, binary, MORPH_CLOSE, kernel, Point(-1, -1));

	morphologyEx(binary, binary, MORPH_OPEN, kernel, Point(-1, -1), 3);
	imshow("binary1", binary);

	// 轮廓发现
	vector<Vec4i> hireachy;
	vector<vector<Point>> contours;
	bitwise_not(binary, binary);
	findContours(binary, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	Mat result = img.clone();
	Point2f center;
	float radius;
	int count = 0;

	// 轮廓分析
	for (size_t i = 0; i < contours.size(); i++) {
		//cout << "硬币个数为: " << contours.size() << endl;
		// 1. 对于面积小于1000的进行椭圆的拟合
		double area = contourArea(contours[i]);
		if (area < 6000) {
			continue;
		}
		if (area > 7000) {
			count++;
		}

		RotatedRect rrt = fitEllipse(contours[i]);
		ellipse(result, rrt, Scalar(255, 0, 124), 2);

		radius = min(rrt.size.width, rrt.size.height) / 2.0;
		circle(result, rrt.center, radius, Scalar(0, 0, 255), 4, 8, 0);
		
		// 找出轮廓的中心位置
		Moments M = moments(contours[i]);
		double cx = M.m10 / M.m00;
		double cy = M.m01 / M.m00;
		circle(result, Point(cx, cy), 2, Scalar(255, 0, 0), 2, 8, 0);
	}
	cout << "硬币个数为: " << count << endl;

	// 显示结果
	imshow("result", result);
	waitKey(0);
}
int main() {
	assignment_one();
	//assignment_two();

	destroyAllWindows();
	return 0;
}
