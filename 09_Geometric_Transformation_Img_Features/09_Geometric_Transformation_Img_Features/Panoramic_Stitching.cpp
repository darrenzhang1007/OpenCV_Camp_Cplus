#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	vector<string> files;
	
	glob("H:/OpenCV_Camp_Cplus/09_Geometric_Transformation_Img_Features/boat/", files);
	vector<Mat> images;
	for (int i = 0; i < files.size(); i++) {
		printf("image file : %s \n", files[i].c_str());
		images.push_back(imread(files[i]));
	}

	// 设置拼接模式与参数
	Mat result1, result2, result3;
	Stitcher::Mode mode = Stitcher::PANORAMA;
	Ptr<Stitcher> stitcher = Stitcher::create(mode);

	// 拼接方式-多通道融合
	auto blender = detail::Blender::createDefault(detail::Blender::MULTI_BAND);
	stitcher->setBlender(blender);

	// 拼接
	Stitcher::Status status = stitcher->stitch(images, result1);

	// 平面曲翘拼接
	auto plane_warper = makePtr<cv::PlaneWarper>();
	stitcher->setWarper(plane_warper);
	status = stitcher->stitch(images, result2);

	// 鱼眼拼接
	auto fisheye_warper = makePtr<cv::FisheyeWarper>();
	stitcher->setWarper(fisheye_warper);
	status = stitcher->stitch(images, result3);

	// 检查返回
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return EXIT_FAILURE;
	}
	imwrite("result1.png", result1);
	imwrite("result2.png", result2);
	imwrite("result3.png", result3);

	waitKey(0);
	return 0;
}