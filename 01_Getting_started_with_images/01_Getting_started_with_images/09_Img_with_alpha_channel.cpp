#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/panther.png";
	// Read the img
	Mat imgPNG = imread(imagePath, -1);
	cout << "image size = " << imgPNG.size() << endl;
	cout << "number of channels = " << imgPNG.channels() << endl;

	Mat imgBGR;
	Mat imgPNGChannels[4];
	split(imgPNG, imgPNGChannels);

	merge(imgPNGChannels, 3, imgBGR);
		
	// 第四个通道是alpha通道
	Mat imgMask = imgPNGChannels[3];
	imshow("Color Channels",imgBGR);
	imshow("Alpha Channel",imgMask);
	waitKey(0);
	return 0;
}