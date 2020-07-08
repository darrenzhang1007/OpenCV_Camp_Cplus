#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// 膨胀操作
	Mat img_dilate = imread("H:/OpenCV_Camp_Cplus/data/images/dilation_example.jpg");
	imshow("img_dilate", img_dilate);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(21, 21), Point(10, 10));
	Mat imgDilated, imgEroded;
	dilate(img_dilate, imgDilated, kernel);
	imshow("imgDilated", imgDilated);

	// 腐蚀操作
	Mat img_erode = imread("H:/OpenCV_Camp_Cplus/data/images/erosion_example.jpg");
	imshow("img_erode", img_erode);
	erode(img_erode, imgEroded, kernel);
	imshow("imgEroded", imgEroded);

	// 开运算
	Mat img_open = imread("H:/OpenCV_Camp_Cplus/data/images/opening.png");
	Mat imgMorphOpened;
	morphologyEx(img_open, imgMorphOpened, MORPH_OPEN, kernel, Point(-1, -1), 3);
	imshow("imgMorphOpened", imgMorphOpened);

	// 闭运算
	Mat img_close = imread("H:/OpenCV_Camp_Cplus/data/images/closing.png");
	Mat imgMorphClosed;
	morphologyEx(img_close, imgMorphClosed, MORPH_CLOSE, kernel, Point(-1, -1), 3);
	imshow("imgMorphClosed", imgMorphClosed);

	waitKey(0);
	destroyAllWindows();
}