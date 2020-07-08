#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	VideoCapture capture;
	capture.open("H:/OpenCV_Camp_Cplus/data/vtest.avi");

	if (!capture.isOpened()) {
		printf("could not open the video file \n");
		return -1;
	}

	int w = capture.get(CAP_PROP_FRAME_WIDTH);
	int h = capture.get(CAP_PROP_FRAME_HEIGHT);
	int fps = capture.get(CAP_PROP_FPS);
	printf("frame width : %d, height : %d, FPS : %d", w, h, fps);

	namedWindow("frame", WINDOW_AUTOSIZE);
	Mat frame;
	while(true) {
		//capture >> frame;
		bool ret = capture.read(frame);
		if (!ret) {
			break;
		}
		imshow("frame", frame);
		char c = waitKey(1);
		if (c == 27) {  // Esc
			break;
		}
	}
	
	waitKey(0);
	destroyAllWindows();
	capture.release();
	return 0;


}