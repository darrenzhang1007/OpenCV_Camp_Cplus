#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/musk.jpg";

	// 1. split channels
	Mat img = imread(imagePath);
	Mat imgchannels[3];
	split(img, imgchannels);

	// 2. write the channels
	imwrite("imgBlue.png", imgchannels[0]);
	imwrite("imgGreen.png", imgchannels[1]);
	imwrite("imgRed.png", imgchannels[2]);

	// 3. show the channels img
	imshow("Blue Channel", imgchannels[0]);
	imshow("Green Channel", imgchannels[1]);
	imshow("Red Channel", imgchannels[2]);
	
	waitKey(0);
	return 0;
}