#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	// ***** 一、Mat类重载 << 操作符，使用流操作输出矩阵内容，并支持不同输出格式 ***** //
	
	// 创建一个3*2的矩阵，并随机初始化元素
	Mat R = Mat(3, 2, CV_8UC3);
	randu(R, Scalar::all(0), Scalar::all(255));

	// 1. 默认输出格式
	cout << " R(default) = " << endl << R << endl;

	// 2. python输出格式
	cout << " R(python) = " << endl << format(R,Formatter::FMT_PYTHON) << endl;

	// 3. Numpy输出格式
	cout << " R(numpy) = " << endl << format(R, Formatter::FMT_NUMPY) << endl;

	// 4. C语言输出格式
	cout << " R(C) = " << endl << format(R, Formatter::FMT_C) << endl;

	// 5. CSV输出格式
	cout << " R(CSV) = " << endl << format(R, Formatter::FMT_CSV) << endl;

	// ***** 二、除了Mat对象，也支持其他类型使用流操作输出内容 ***** //
	// 1. 二维点
	Point2f P1(5, 1);
	cout << "point (2d) = " << P1 << endl;
	// 2. 三维点
	Point3f P2(5, 1, 8);
	cout << "Point (3d) = " << P2 << endl;

	getchar();
	return 0;
}