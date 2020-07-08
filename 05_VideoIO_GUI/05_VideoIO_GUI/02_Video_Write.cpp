#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	VideoCapture capture(0);
	// check open
	if (!capture.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter outavi("H:/output.avi", cv::VideoWriter::fourcc('M', 'P', '4', '2'), 10, Size(frame_width, frame_height));
	VideoWriter outmp4("H:/output.mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 10, Size(frame_width, frame_height));

	// Ð´ÊÓÆµ
	while (true) {
		Mat frame;
		bool ret = capture.read(frame);
		if (!ret) {
			break;
		}
		// write the frame	
		outavi.write(frame);
		outmp4.write(frame);

		imshow("Frame", frame);
		// Esc
		char c = (char)waitKey(1);
		if (c == 27) {
			break;
		}		
	}
	// When everything done, release the video capture object
	capture.release();
	outavi.release();
	outmp4.release();

	// Closes all the frames
	destroyAllWindows();
	return 0;
}