#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int patch_width = 60;
int patch_height = 60;

static void onMouse(int event, int x, int y, int flags, void* data) {
	Mat image = *((Mat*)data);
	if (event == EVENT_LBUTTONDOWN) {
		printf("current location Point(%d, %d) \n", x, y);
		Rect patch_rect(x - patch_width / 2, y - patch_height / 2, patch_width, patch_height);
		Mat patch = image(patch_rect);

		// 将60*60分成9个20*20的grid
		Mat sub_patch[9];
		sub_patch[0] = patch(Range(0, patch_height / 3), Range(0, patch_width / 3));
		sub_patch[1] = patch(Range(0, patch_height / 3), Range(patch_width / 3, 2 * patch_width / 3));
		sub_patch[2] = patch(Range(0, patch_height / 3), Range(2 * patch_width / 3, patch_width));

		sub_patch[3] = patch(Range(patch_height / 3, 2 * patch_height / 3), Range(0, patch_width / 3));
		sub_patch[4] = patch(Range(patch_height / 3, 2 * patch_height / 3), Range(patch_width / 3, 2 * patch_width / 3));
		sub_patch[5] = patch(Range(patch_height / 3, 2 * patch_height / 3), Range(2 * patch_width / 3, patch_width));

		sub_patch[6] = patch(Range(2 * patch_height / 3, patch_height), Range(0, patch_width / 3));
		sub_patch[7] = patch(Range(2 * patch_height / 3, patch_height), Range(patch_width / 3, 2 * patch_width / 3));
		sub_patch[8] = patch(Range(2 * patch_height / 3, patch_height), Range(2 * patch_width / 3, patch_width));

		// 2. 然后对9个区域做拉普拉斯运算
		Mat sub_patch_laplacian[9];
		for (int i = 0; i < 9; i++) {
			Laplacian(sub_patch[i], sub_patch_laplacian[i], CV_32F, 3, 1, 0);
		}
		float sub_patch_mean[9];
		for (int i = 0; i < 9; i++) {
			sub_patch_mean[i] = (mean(sub_patch_laplacian[i])).val[0];
		}
		float min_mean = sub_patch_mean[0];
		int min_index = 0;  // 最小的mean代表着平整的区域，不是边缘区域
		for(int i = 0; i < 9; i++){
			if (sub_patch_mean[i] < min_mean) {
				min_mean = sub_patch_mean[i];
				min_index = i;
			}
		}
		Mat out;
		Mat src_mask = Mat::ones(sub_patch[min_index].rows, sub_patch[min_index].cols, sub_patch[min_index].depth());
		src_mask = 255 * src_mask;

		// 用周围低对比度的像素去修复高对比度的像素
		seamlessClone(sub_patch[min_index], image, src_mask, Point(x, y), image, NORMAL_CLONE);  // 泊松融合
		// 泊松融合 将sub_patch的图融合src_mask处，然后在替换到原图image的(x,y)处
		imshow("祛斑效果演示", image);
	}
	if (event == EVENT_RBUTTONDOWN) {
		Mat dst;
		bilateralFilter(image, dst, 0, 50, 5);
		imshow("磨皮效果展示", dst);
	}
}

int main(int argc, char** argv) {
	Mat img = imread("H:/OpenCV_Camp_Cplus/data/images/blemish.png");
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", img);
	setMouseCallback("input", onMouse, &img);
	waitKey(0);
	return 0;
}


