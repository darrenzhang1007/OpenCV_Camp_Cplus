#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/QRcode.jpg");
	if (img.empty()) {
		cout << "请输入正确的图像" << endl;
		return -1;
	}
	Mat gray, qrcode;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	QRCodeDetector qrcodedetector;
	vector<Point> points;
	string information;
	bool isQRcode;
	isQRcode = qrcodedetector.detect(gray, points); //识别二维码
	if (isQRcode) {
		// 解析二维码
		information = qrcodedetector.decode(gray, points, qrcode);
		cout << points << endl;  // 输出四个顶点坐标
		cout << information << endl;  // 输出四个顶点坐标

	}
	else {
		cout << "无法识别二维码" << endl;
		return -1;
	}

	// 绘制边框
	for (int i = 0; i < points.size(); i++) {
		if (i == points.size() - 1) {
			line(img, points[i], points[0], Scalar(0, 0, 255), 2, 8);
			break;
		}
		line(img, points[i], points[i+1], Scalar(0, 0, 255), 2, 8);
	}

	// 将qr码的内容输出到图片上
	putText(img, information.c_str(), Point(20, 30), 0, 1.0, Scalar(0, 0, 255), 2, 8);

	string information2;
	vector<Point> points2;
	information2 = qrcodedetector.detectAndDecode(gray, points2);
	cout << information2 << endl;  


	imshow("result", img);
	//namedWindow("qrcode_bin", WINDOW_AUTOSIZE);
	//imshow("qrcode_bin", qrcode);
	waitKey();
	return 0;

}