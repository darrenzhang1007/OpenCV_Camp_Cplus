#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	VideoCapture cap(0);
	Mat frame;
	int k = 0;

	// Detect if it is working properly
	if (!cap.isOpened())
	{
		cout << "Unable to open the file " << "\n";
		return -1;
	}
	else
	{
		while (1)
		{
			// read
			cap >> frame;
			if (k == 27)
				break;
			// Identify if 'e' or 'E' is pressed
			if (k == 101 || k == 69)
				putText(frame, "E is pressed, press Z or ESC", Point(100, 180), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 3);
			// Identify if 'z' or 'Z' is pressed or not
			if (k == 90 || k == 122)
				putText(frame, "Z is pressed", Point(100, 180), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 3);
			imshow("Image", frame);
			k = waitKey(10) & 0xFF;
		}
	}
	cap.release();
	destroyAllWindows();
	return 0;
}