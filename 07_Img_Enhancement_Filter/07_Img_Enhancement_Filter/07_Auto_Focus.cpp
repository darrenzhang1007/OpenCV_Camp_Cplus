#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <cstdio>

using namespace std;
using namespace cv;
void method_one();
void method_two();

int main(int argc, char** argv) {
	//method_one();
	method_two();
	return 0;
}

void method_one() {
	VideoCapture capture;
	capture.open("H:/OpenCV_Camp_Cplus/data/focus-test.mp4");
	if (!capture.isOpened()) {
		printf("could not load video...\n");
		return;
	}
	int h = capture.get(CAP_PROP_FRAME_HEIGHT);
	int w = capture.get(CAP_PROP_FRAME_WIDTH);
	Mat frame, gray;
	float dev = 0;
	float max = -1;
	char buffer[20];
	Mat temp = Mat::zeros(Size(w, h), CV_32FC1);
	Mat mean, stddev;
	VideoWriter outmp4("H:/output.mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 10, Size(w, h));

	while (true) {
		bool ret = capture.read(frame);
		if (!ret) {
			break;
		}
		imshow("frame", frame);
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		for (int row = 1; row < h - 1; row++) {
			for (int col = 1; col < w - 1; col++) {
				int dx = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row, col + 1) - gray.at<uchar>(row, col - 1);
				int dy = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row + 1, col) - gray.at<uchar>(row - 1, col);
				temp.at<float>(row, col) = abs(dx + dy);
			}
		}
		meanStdDev(temp, mean, stddev);
		dev = stddev.at<double>(0, 0);
		sprintf_s(buffer, "%.2f", dev);
		putText(frame, buffer, Point(20, 30), 1, 2.0, Scalar(0, 0, 255), 2, 8);
		printf("stddev: %.2f\n", dev);
		imshow("dev show", frame);
		outmp4.write(frame);
		if (max < dev) {
			max = dev;
			imwrite("sharpen.png", frame);
		}
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	outmp4.release();
	Mat result = imread("sharpen.png");
	imshow("best img", result);
	waitKey(0);
	destroyAllWindows();
}

void method_two() {
	VideoCapture capture;
	capture.open("H:/OpenCV_Camp_Cplus/data/focus-test.mp4");
	if (!capture.isOpened()) {
		printf("could not load video...\n");
		return;
	}
	int h = capture.get(CAP_PROP_FRAME_HEIGHT);
	int w = capture.get(CAP_PROP_FRAME_WIDTH);
	Mat frame, gray;
	float sum = 0;
	float max = -1;
	char buffer[20];
	VideoWriter outmp4("H:/output2.mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 10, Size(w, h));

	while (true) {
		bool ret = capture.read(frame);
		if (!ret) {
			break;
		}
		imshow("frame", frame);
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		for (int row = 1; row < h - 1; row++) {
			for (int col = 1; col < w - 1; col++) {
				int dx = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row, col + 1) - gray.at<uchar>(row, col - 1);
				int dy = gray.at<uchar>(row, col) * 2 - gray.at<uchar>(row + 1, col) - gray.at<uchar>(row - 1, col);
				sum += (abs(dx) + abs(dy));
			}
		}
		sprintf_s(buffer, "%.2f", sum);
		putText(frame, buffer, Point(20, 30), 1, 2.0, Scalar(0, 0, 255), 2, 8);
		printf("stddev: %.2f\n", sum);
		imshow("dev show", frame);
		outmp4.write(frame);
		if (max < sum) {
			max = sum;
			imwrite("sharpen2.png", frame);
		}
		sum = 0;
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	Mat result = imread("sharpen2.png");
	imshow("×î¼ÑÇåÎú¶È", result);
	waitKey(0);
	destroyAllWindows;
}