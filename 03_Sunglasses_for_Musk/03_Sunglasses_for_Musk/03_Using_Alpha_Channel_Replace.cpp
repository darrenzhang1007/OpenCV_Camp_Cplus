#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int main(void) {
	// Load the Face Image
	string faceImagePath = "H:/OpenCV_Camp_Cplus/data/images/musk.jpg";
	Mat faceImage = imread(faceImagePath);
	// Load the Sunglass image with Alpha channel
	string glassMaskPath = "H:/OpenCV_Camp_Cplus/03_Sunglasses_for_Musk/03_Sunglasses_for_Musk/sunglassAlpha.png";
	Mat glassMask1 = imread(glassMaskPath, 0);

	// Load the Sunglass image with BGR channel
	string glassBGRPath = "H:/OpenCV_Camp_Cplus/03_Sunglasses_for_Musk/03_Sunglasses_for_Musk/sunglassRGB.png";
	Mat glassBGR = imread(glassBGRPath);

	Mat glassMask;
	// 因为人脸图像是三通道图像，也生成3通道的mask图像
	Mat glassMaskChannels[] = {glassMask1, glassMask1, glassMask1};
	merge(glassMaskChannels, 3, glassMask);
	glassMask = glassMask / 255;

	// 复制人脸图像
	Mat faceWithGlassesArithmetic = faceImage.clone();

	// 选取眼睛区域
	Mat eyeROI = faceWithGlassesArithmetic(Range(150, 250), Range(140, 440));

	Mat eyeROIChannels[3];
	split(eyeROI, eyeROIChannels);
	Mat maskedEyeChannels[3];
	Mat maskedEye;

	for (int i = 0; i < 3; i++) {
		// 根据墨镜mask图像生成眼睛区域的mask图像
		multiply(eyeROIChannels[i], (1 - glassMaskChannels[i]), maskedEyeChannels[i]);
	}
	merge(maskedEyeChannels, 3, maskedEye);
	imshow("Masked eye region", maskedEye);

	Mat maskedGlass;
	// 根据mask图像生成掩膜的墨镜区域
	multiply(glassBGR, glassMask, maskedGlass);
	imshow("Masked Sunglass Region", maskedGlass);

	Mat eyeRoiFinal;
	// 将墨镜和眼睛区域合并获得最终的效果
	add(maskedEye, maskedGlass, eyeRoiFinal);
	imshow("Augmented Eye and Sunglass", eyeRoiFinal);

	// 将戴墨镜的眼睛图像复制到人脸图像上
	eyeRoiFinal.copyTo(eyeROI);
	imwrite("withSunglasses.png", faceWithGlassesArithmetic);
	imshow("With Sunglasses", faceWithGlassesArithmetic);
	waitKey(0);

	return 0;
}