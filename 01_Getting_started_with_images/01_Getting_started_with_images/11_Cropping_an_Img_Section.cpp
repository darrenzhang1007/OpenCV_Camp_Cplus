#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/boy.jpg";
	Mat img = imread(imagePath);
	cout << "img`s size is " << img.size() << endl;

	// 1. 从原始图像中裁剪出一块区域
	Mat crop = img(Range(40, 200), Range(170, 320));

	imshow("Cropped image",crop);

	// 2. 创建mask
	Mat mask1 = Mat::zeros(img.size(), img.type());
	imshow("Mask1", mask1);
	mask1(Range(40, 200), Range(170, 320)).setTo(255);
	imshow("Mask 1 Revised", mask1);

	Mat mask2;
	inRange(img, Scalar(0, 0, 150), Scalar(100, 100, 255), mask2);
	imshow("Mask 2", mask2);


	waitKey(0);
	return 0;

}