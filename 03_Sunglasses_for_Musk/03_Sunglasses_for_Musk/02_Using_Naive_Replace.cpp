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
	string glassimagePath = "H:/OpenCV_Camp_Cplus/03_Sunglasses_for_Musk/03_Sunglasses_for_Musk/sunglassRGB.png";
	Mat glassImg = imread(glassimagePath);
	imshow("Face with roiFace glassImg glasses Naive", glassImg);

	// make a copy 
	Mat faceWithGlassesNaive = faceImage.clone();
	Mat roiFace = faceWithGlassesNaive(Range(150, 250), Range(140, 440));
	imshow("Face with roiFace Naive", roiFace);

	glassImg.copyTo(roiFace);
	imshow("Face with roiFace with glasses Naive", roiFace);

	imshow("Face with Glasses Naive", faceWithGlassesNaive);
	waitKey(0);

	return 0;
}



		