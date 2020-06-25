#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	/*********** 一、使用Mat ***********/
	Mat grayImg(480, 640, CV_8UC1);
	for (int i = 0; i < grayImg.rows; i++) {
		// 1. 获取第i行第一个像素的指针
		uchar* p = grayImg.ptr<uchar>(i);
		for (int j = 0; j < grayImg.cols; j++) {
			double d1 = (double)((i + j) % 255);
			// 2. 用 at() 读写像素，需要制定元素类型
			grayImg.at<uchar>(i, j) = d1;
			// 3. 如果使用下面代码，对于元素类型指定错误，会报错
			//double d2 = grayImg.at<double>(i, j);
		}
	}

	/*********** 二、使用Mat_ ***********/
	// 需要在声明变量时指定矩阵的元素类型
	Mat_<uchar> grayImg1 = (Mat_<uchar>&)grayImg;
	for (int i = 0; i < grayImg1.rows; i++) {
		// 获取第i行的首个像素的指针，这里不需要在指定元素类型
		uchar* p = grayImg1.ptr(i);
		for (int j = 0; j < grayImg1.cols; j++) {
			double d1 = (double)((i + j) % 255);
			// 直接使用MATLAB风格的矩阵元素读写，简洁
			grayImg1(i, j) = d1;
			double b2 = grayImg1(i, j);
		}
	}
	return 0;
}