#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/threshold.png");
	imshow("input", img);
	Mat gray, thre;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//double ret = threshold(gray, thre, 127, 255, THRESH_BINARY | THRESH_OTSU);
	double ret = threshold(gray, thre, 127, 255, THRESH_BINARY | THRESH_TRIANGLE);

	//adaptiveThreshold(gray, thre, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 25, 10);
	cout << "threshold is " << ret << endl;
	imshow("thre", thre);
	waitKey(0);
	destroyAllWindows();
}