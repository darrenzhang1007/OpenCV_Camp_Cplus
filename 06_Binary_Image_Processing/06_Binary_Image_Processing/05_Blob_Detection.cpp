#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <time.h>

using namespace std;
using namespace cv;

int main() {
	// Read image
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/blob_detection.jpg", IMREAD_GRAYSCALE);
	imshow("input", img);

	// Set up detector with default parameters
	//Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();
	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 10;
	params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 50;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;

	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	std::vector<KeyPoint> keypoints;
	detector->detect(img, keypoints);

	// Mark blobs using image annotation concepts we have studied so far
	int x, y;
	int radius;
	double diameter;
	cvtColor(img, img, COLOR_GRAY2BGR);
	for (int i = 0; i < keypoints.size(); i++) {
		KeyPoint k = keypoints[i];
		Point keyPt;
		keyPt = k.pt;
		x = (int)keyPt.x;
		y = (int)keyPt.y;
		// Mark center in BLACK
		circle(img, Point(x, y), 5, Scalar(255, 0, 0), -1);
		// Get radius of coin
		diameter = k.size;
		radius = (int)diameter / 2.0;
		// Mark blob in GREEN
		circle(img, Point(x, y), radius, Scalar(0, 255, 0), 2);
	}

	imshow("Image", img);
	waitKey(0);
}