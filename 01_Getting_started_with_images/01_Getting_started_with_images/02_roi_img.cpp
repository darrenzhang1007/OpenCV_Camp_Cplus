#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	// 创建一个单位矩阵
	Mat A = Mat::eye(10, 10, CV_32S);
	// 取出A矩阵的第i行
	Mat line = A.row(1);
	// 取出A矩阵的第i行，将这一行元素乘2在赋值给j行
	A.row(2) = A.row(2) * 2;
	cout << "A = " << endl << A << endl;

	// 提取第一列到第三列（不包含第三列）
	Mat B = A(Range::all(), Range(1, 3));
	// 提取B的第5行到第9行（不包含第9行）
	Mat C = B(Range(5, 9), Range::all());

	// ******** 上述代码等价 ******** //
	Mat D = A(Range(5, 9), Range(1, 3));

	// ************ ROI ************* //
	Mat img(Size(320, 240), CV_8UC3);
	// 选取img中的Rect(10, 10, 100, 100)的区域为ROI
	// 1. 使用构造函数
	Mat roi(img, Rect(10, 10, 100, 100));
	Mat roi2(img, Range(10, 100), Range(10, 100));
	// 2. 使用括号运算符
	Mat roi3 = img(Rect(10, 10, 100, 100));
	Mat roi4 = img(Range(10, 100), Range(10, 100));
	imshow("img", img);
	imshow("img1", roi);
	imshow("img2", roi2);
	imshow("img3", roi3);
	imshow("img4", roi4);

	// ************ 选取对角线 ************* //
	Mat M = (Mat_<int>(4, 4) <<
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 0, 8, 7,
		6, 5, 4, 2);
	// 1. 取主对角线
	Mat d0 = M.diag(0);
	cout << "d0=" << endl << d0 << endl;
	// 2. 取主对角线上方第2条对角线
	Mat d1 = M.diag(2);
	cout << "d1=" << endl << d1 << endl;
	// 3. 取主对角线下方第1条对角线
	Mat d2 = M.diag(-1);
	cout << "d2=" << endl << d2 << endl;

	waitKey();

	return 0;
}