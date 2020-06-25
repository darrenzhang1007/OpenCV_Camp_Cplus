#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main(void) {
	// Load the Face Image
	string faceImagePath = "H:/OpenCV_Camp_Cplus/data/images/musk.jpg";
	Mat faceImage = imread(faceImagePath);
	// Load the Sunglass image with Alpha channel
	string glassimagePath = "H:/OpenCV_Camp_Cplus/data/images/sunglass.png";
	Mat glassImg = imread(glassimagePath);

	// Read the image
	Mat glassPNG = imread(glassimagePath, -1);
	// Resize the image to fit over the eye region
	resize(glassPNG, glassPNG, Size(300, 100));

	cout << "Image Dimension = " << glassPNG.size() << endl;
	cout << "Number of channels = " << glassPNG.channels();

	// Separate the Color and alpha channels
	Mat glassRGBAChannels[4];
	Mat glassRGBChannels[3];
	split(glassPNG, glassRGBAChannels);

	for (int i = 0; i < 3; i++) {
		// Copy R,G,B channel from RGBA to RGB
		glassRGBChannels[i] = glassRGBAChannels[i];
	}

	Mat glassBGR, glassMask;
	// Prepare BGR Image
	merge(glassRGBChannels, 3, glassBGR);
	// Alpha channel is the 4th channel in RGBA Image
	glassMask = glassRGBAChannels[3];

	imwrite("sunglassRGB.png", glassBGR);
	imwrite("sunglassAlpha.png", glassMask);

	imshow("sunglassRGB.png", glassBGR);
	imshow("sunglassAlpha.png", glassMask);
	waitKey();
	return 0;
}
