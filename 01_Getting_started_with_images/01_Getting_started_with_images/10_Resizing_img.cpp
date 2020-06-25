#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/boy.jpg";
	Mat img = imread(imagePath);
	cout << "img`s size is " << img.size() << endl;

	int resizeDownWidth = 300;
	int resizeDownHeight = 200;
	Mat resizedDownImg;
	resize(img, resizedDownImg, Size(resizeDownWidth, resizeDownHeight), INTER_LINEAR);
	cout << "resizedDownImg Image size = " << resizedDownImg.size() << endl;

	int resizeUpWidth = 600;
	int resizeUpHeight = 900;
	Mat resizedUpImg;
	resize(img, resizedUpImg, Size(resizeUpWidth, resizeUpHeight), INTER_LINEAR);
	cout << "resizedUpImg Image size = " << resizedUpImg.size() << endl;

	imshow("resizeUpImg", resizedUpImg);
	imshow("resizeDownImg", resizedDownImg);

	// 等比例放大1.5倍，缩小0.5倍
	double scaleUp = 1.5;
	double scaleDown = 0.5;
	Mat scaledUpImg, scaledDownImg;
	resize(img, scaledUpImg, Size(), scaleUp, scaleUp, INTER_LINEAR);
	resize(img, scaledDownImg, Size(), scaleDown, scaleDown, INTER_LINEAR);

	imshow("Scaled Up", scaledUpImg);
	imshow("Scaled Down", scaledDownImg);

	cout << "Scaled Up Image size = " << scaledUpImg.size() << endl;
	cout << "Scaled Down Image size = " << scaledDownImg.size() << endl;
	
	waitKey(0);
	return 0;
}