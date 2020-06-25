#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat A = Mat::eye(4, 4, CV_32SC1);
	Mat B = A * 3 + 1;  // Mat * scalar + scalar
	Mat C = B.diag(0) + B.col(1);  // Mat + Mat

	cout << "A=" << endl << A << endl << endl;
	cout << "B=" << endl << B << endl << endl;
	cout << "C=" << endl << C << endl << endl;
	cout << "C .* diag(B)=" << endl << C.dot(B.diag(0)) << endl << endl;

	getchar();
	return 0;
}