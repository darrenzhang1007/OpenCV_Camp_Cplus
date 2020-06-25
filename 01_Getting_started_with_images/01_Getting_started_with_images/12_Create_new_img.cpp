#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/boy.jpg";
	Mat img = imread(imagePath);
	cout << "img`s size is " << img.size() << endl;

	Mat imgCopy = img.clone();
	Mat emptyMatrix = Mat(100, 200, CV_8UC3, Scalar(0, 0, 0));
	imshow("emptyMatrix", emptyMatrix);

	emptyMatrix.setTo(Scalar(255, 255, 255));
	imshow("emptyMatrix", emptyMatrix);

	Mat emptyOriginal = Mat(emptyMatrix.size(),
		emptyMatrix.type(), Scalar(100, 100, 100));
	imshow("Empty Original",emptyOriginal);

	/****** 二、复制图像中的一块区域放在另外的地方 ******/
	Mat copiedImg = img.clone();
	Mat copyRoi = img(Range(40, 200), Range(180, 320));

	int roiHeight = copyRoi.size().height;
	int roiWidth = copyRoi.size().width;

	copyRoi.copyTo(copiedImg(Range(40, 40 + roiHeight), Range(10, 10 + roiWidth)));
	copyRoi.copyTo(copiedImg(Range(40, 40 + roiHeight), Range(330, 330 + roiWidth)));
	imshow("Output Image", copiedImg);
	waitKey(0);

	waitKey();
	return 0;
}