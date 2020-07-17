#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void sketch_filter(Mat &img);
void cartoonify(Mat &img);

int main(int argc, char** argv){
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/reba.jpg");
	namedWindow("input", WINDOW_FREERATIO);
	imshow("input", img);
	sketch_filter(img);
	waitKey(0);


	//VideoCapture cap(0);
	//Mat frame;
	//while (true) {
	//	bool ret = cap.read(frame);
	//	imshow("input", frame);
	//	if (!ret) {
	//		break;
	//	}
	//	//sketch_filter(frame);
	//	cartoonify(frame);
	//	char c = waitKey(1);
	//	if (c == 27) {
	//		break;
	//	}
	//}
	waitKey(0);
	destroyAllWindows();
}

void sketch_filter(Mat &img){
	double t1 = getTickCount();
	// 转换成灰度图
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 取反与高斯模糊
	Mat invert;
	bitwise_not(gray, invert);
	GaussianBlur(invert, invert, Size(15, 15), 0);
	
	// 图像去饱和公式
	// 减淡公式：C = MIN(A + (A*B) / (255 - B), 255)
	// 其中C为混合结果，A为去色后的像素点，B为高斯后的像素点
	Mat result(gray.size(), CV_8UC1);
	for (size_t row = 0; row < gray.rows; row++) {
		uchar* g_pixel = gray.data + row*gray.step;
		uchar* in_pixel = invert.data + row*invert.step;
		uchar* result_row = result.data + row*result.step;

		for (size_t col = 0; col < gray.cols; col++) {
			int a = *g_pixel++;
			int b = *in_pixel++;
			int c = std::min(a + (a*b) / (255 - b), 255);
			*result_row++ = c;
		}
	}
	gray.release();
	invert.release();
	double t2 = getTickCount();
	double fps = getTickFrequency() / (t2 - t1);
	putText(result, format("current FPS: %.2f", fps), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 2, 8);
	namedWindow("sketch filter result", WINDOW_FREERATIO);
	imshow("sketch filter result", result);

}

void cartoonify(Mat &img) {
	Mat blur_tmp;
	Mat tmp;
	int kernel_size = 11;
	double sigmaColor = 9;
	double sigmaSpace = 7;
	bilateralFilter(img, tmp, kernel_size, sigmaColor, sigmaSpace);
	for (int i = 0; i < 14; i++) {
		bilateralFilter(tmp, blur_tmp, kernel_size, sigmaColor, sigmaSpace);
		tmp = blur_tmp.clone();
	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(3, 3), 3, 3);
	Mat edge_tmp;
	const int LAPLACIAN_FILTER_SIZE = 5;
	Laplacian(gray, edge_tmp, CV_8U, LAPLACIAN_FILTER_SIZE);
	threshold(edge_tmp, edge_tmp, 127, 255, THRESH_BINARY_INV);

	for (int row = 0; row < edge_tmp.rows; row++) {
		for (int col = 0; col < edge_tmp.cols; col++) {
			if (edge_tmp.at<uchar>(row, col) == 0) {
				blur_tmp.at<Vec3b>(row, col)[0] = 0;
				blur_tmp.at<Vec3b>(row, col)[1] = 0;
				blur_tmp.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	blur_tmp;
	imshow("cartoon", blur_tmp);
}