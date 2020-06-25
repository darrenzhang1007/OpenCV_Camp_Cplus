#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/number_zero.jpg";

	// Read this img in Grayscale Format
	Mat testImg = imread(imagePath, 0);  // Read the img
	cout << testImg << endl;

	/**************** 一、改变某个像素的值 ****************/
	cout << (int)testImg.at<uchar>(0, 0) << endl;
	testImg.at<uchar>(0, 0) = 200;
	cout << testImg << endl;

	/**************** 二、改变某个区域像素的值 ****************/
	Mat roi_img = testImg(Range(0, 2), Range(0, 4));
	cout << "Selected Region\n" << roi_img << endl;

	testImg(Range(0, 2), Range(0, 4)).setTo(111);
	cout << "Modified Matrix\n" << testImg << endl;

	/**************** 三、改变彩色图像某个区域三通道的像素的值 ****************/
	Mat testImg_color = imread(imagePath, 1);
	cout << "image size = " << testImg_color.size() << endl;

	cout << testImg_color.at<Vec3b>(0, 0) << endl;

	testImg_color.at<Vec3b>(0, 0) = Vec3b(0, 255, 255);
	imwrite("zero1.png", testImg_color);  // 图像保存
	imshow("Zero 1", testImg_color);

	testImg_color.at<Vec3b>(1, 1) = Vec3b(255, 255, 0);
	imwrite("zero2.png", testImg_color);
	imshow("Zero 2", testImg_color);

	testImg_color.at<Vec3b>(2, 2) = Vec3b(255, 0, 255);
	imwrite("ero3.png", testImg_color);
	imshow("Zero 3", testImg_color);

	waitKey(0);

	getchar();
	return 0;
}
