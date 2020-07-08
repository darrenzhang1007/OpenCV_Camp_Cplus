#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Points to store the center of the circle and a point on the circumference
Point tl, br;
// Source image
Mat source;
// function which will be called on mouse input
void drawCircle(int event, int x, int y, int flags, void *userdata) {
	// Action to be taken when left mouse button is pressed
	if (event == EVENT_LBUTTONDOWN) {
		tl = Point(x, y);
		// Mark the center
		circle(source, tl, 1, Scalar(255, 255, 0), 2, LINE_AA);
	}
	// Action to be taken when left mouse button is released
	else if (event == EVENT_LBUTTONUP) {
		br = Point(x, y);
		int w = br.x - tl.x;
		int h = br.y - tl.y;
		Rect rect;
		rect.x = tl.x;
		rect.y = tl.y;
		rect.width = w;
		rect.height = h;
		imwrite("roiface.png", source(rect));
		circle(source, br, 1, Scalar(0, 255, 0), 2, LINE_AA);
		rectangle(source, rect, Scalar(0, 0, 255), 2, 8, 0);
		imshow("Window", source);
	}
}


int main(int argc, char** argv) {
	source = imread("H:/OpenCV_Camp_Cplus/data/lena.jpg");
	// Make a dummy image, will be useful to clear the drawing
	Mat dummy = source.clone();
	namedWindow("Window");

	// 注册鼠标回调事件响应函数
	setMouseCallback("Window", drawCircle);
	int k = 0;
	// loop until escape character is pressed
	while (k != 27) {
		imshow("Window", source);
		putText(source, "Choose center, and drag, Press ESC to exit and c to clear", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 2);
		k = waitKey(20) & 0xFF;
		if (k == 99)
			// Another way of cloning
			dummy.copyTo(source);
	}
	return 0;
}