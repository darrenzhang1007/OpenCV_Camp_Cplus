#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// Read image as grayscale
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/truth.png", IMREAD_GRAYSCALE);

	// Threshold Img
	Mat imgThresh;
	threshold(img, imgThresh, 127, 255, THRESH_BINARY);
	imshow("img", imgThresh);

	// Find connected components
	Mat imgLabels;
	int nComponents = connectedComponents(imgThresh, imgLabels);
	Mat imgLabelsCopy = imgLabels.clone();

	// First Let`s find the min and max values in imgLabels;
	Point minLoc, maxLoc;
	double minVal, maxVal;

	// The following line finds the min and max pixel values and their locations in an img
	minMaxLoc(imgLabels, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "\n" << minVal << maxVal << minLoc << maxLoc << endl;

	// Normalize the image so the min value is 0 and max value is 255.
	imgLabels = 255 * (imgLabels - minVal) / (maxVal - minVal);

	// Convert image to 8-bits
	imgLabels.convertTo(imgLabels, CV_8U);
	imshow("image", imgLabels);

	// Make a copy of the img
	Mat imgLabel;
	imgLabel = imgLabelsCopy.clone();

	// Display the labels
	cout << "Number of components = " << nComponents;

	for (int i = 0; i < 6; i++) {
		imshow("imgLabels", imgLabel == i);
		waitKey(0);
	}
	
	// Apply a color map
	Mat imColorMap;
	applyColorMap(imgLabels, imColorMap, COLORMAP_JET);

	// Display colormapped labels
	imshow("imColorMap", imColorMap);
	waitKey(0);

	waitKey(0);
	destroyAllWindows();
	return 0;
}