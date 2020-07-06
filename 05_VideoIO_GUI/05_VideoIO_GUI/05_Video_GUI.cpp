#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int maxScaleUp = 100;
int scaleFactor = 1;
int scaleType = 0;
int maxType = 1;
Mat img;

string windowName = "Resize Image";
string trackbarValue = "Scale";
string trackbarType = "Type: \n 0: Scale Up \n 1: Scale Down";

void scaleImage(int, void*) {
	double scaleFactorDouble;
	if (scaleType == 0) {
		scaleFactorDouble = 1 + scaleFactor / 100.0;
	}
	if (scaleType == 1) {
		scaleFactorDouble = 1 - scaleFactor / 100.0;
	}

	Mat scaledImage;
	resize(img, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
	imshow(windowName, scaledImage);
}

int main(int argc, char** argv) {
	img = imread("H:/OpenCV_Camp_Cplus/data/lena.jpg");

	// Create a window to display results
	namedWindow(windowName, WINDOW_AUTOSIZE);
	createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
	createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

	scaleImage(25, 0);

	while (true) {
		int c;
		c = waitKey(20);
		if (static_cast<char>(c) == 27)
			break;
	}

	return 0;
}