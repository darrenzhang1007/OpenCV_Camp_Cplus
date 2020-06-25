#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat grayImg(480, 480, CV_8UC1);
	Mat colorImg(480, 640, CV_8UC3);

	/*at()函数的效率不高，不推荐使用at()函数遍历图像*/
	// 遍历灰度图像所有的像素，并设置像素
	//for (int i = 0; i < grayImg.rows; i++) {
	//	for (int j = 0; j < grayImg.cols; j++) {
	//		grayImg.at<uchar>(i, j) = (i + j) % 255;
	//	}
	//}

	//// 遍历所有彩色图像所有像素，并设置像素值
	//for (int i = 0; i < grayImg.rows; i++) {
	//	for (int j = 0; j < grayImg.cols; j++) {
	//		Vec3b pixel;
	//		pixel[0] = i % 255; // blue
	//		pixel[1] = j % 255; // green
	//		pixel[2] = 0;
	//		colorImg.at<Vec3b>(i, j) = pixel;
	//	}
	//}


	//// ********************* 使用迭代器 ********************* //
	//// 遍历灰度图像所有的像素，并设置像素
	//MatIterator_<uchar> grayItr, grayEnd;
	//for (grayItr = grayImg.begin<uchar>(),
	//	grayEnd = grayImg.end<uchar>();
	//	grayItr != grayEnd; grayItr++
	//	) {
	//	*grayItr = rand() % 255;
	//}

	//// 遍历彩色图像所有的像素，并设置像素
	//MatIterator_<Vec3b> colorItr, colorEnd;
	//for (colorItr = colorImg.begin<Vec3b>(),
	//	colorEnd = colorImg.end<Vec3b>();
	//	colorItr != colorEnd; colorItr++) {
	//	(*colorItr)[0] = rand() % 255; // Blue
	//	(*colorItr)[1] = rand() % 255; // Green
	//	(*colorItr)[2] = rand() % 255; // Red
	//}
	
	// ********************* 使用指针 ********************* //
	for (int i = 0; i < grayImg.rows; i++) {
		// 获取第i行首像素指针
		uchar* p = grayImg.ptr<uchar>(i);
		for (int j = 0; j < grayImg.cols; j++) {

		}
	}


	// 显示结果
	imshow("grayImg", grayImg);
	imshow("colorImg", colorImg);
	waitKey(0);
	return 0;
}