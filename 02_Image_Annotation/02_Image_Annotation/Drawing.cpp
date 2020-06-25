#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imagePath = "H:/OpenCV_Camp_Cplus/data/images/boy.jpg";
	Mat img = imread(imagePath);
	Mat copiedImg = img.clone();

	cout << "img`s size is " << img.size() << endl;

	// 1. draw a circle
	//circle(copiedImg, Point(250, 125), 100, Scalar(0, 0, 255), 5, LINE_AA);

	// 2. draw a filled circle
	//circle(copiedImg, Point(250, 125), 100, Scalar(0, 0, 255), -1, LINE_AA);

	// 3.draw an ellipse
	// Note: Ellipse Centers and Axis lengths must be integers

	//ellipse(copiedImg, Point(250, 125), Point(100, 50), 0, 0, 360,
	//	Scalar(255, 0, 0), 3, LINE_AA);

	//ellipse(copiedImg, Point(250, 125), Point(100, 50), 90, 0, 360,
	//	Scalar(0, 0, 255), 3, LINE_AA);

	// Incomplete/Open ellipse
	//ellipse(copiedImg, Point(250, 125), Point(100, 50), 0, 180, 360,
	//	Scalar(255, 0, 0), 3, LINE_AA);

	// Filled ellipse
	//ellipse(copiedImg, Point(250, 125), Point(100, 50), 0, 0, 180,
	//	Scalar(0, 0, 255), -2, LINE_AA);

	// 4. draw line
	//line(copiedImg, Point(200, 80), Point(280, 80), Scalar(0, 255, 0), 3, LINE_AA);

	// 5. draw rect
	rectangle(copiedImg, Point(170, 50), Point(300, 200),
		Scalar(255, 0, 255), 5, LINE_8);

	// 6. put text on image
	string text = "I am studying";
	double fontScale = 1.5;
	int fontFace = FONT_HERSHEY_SIMPLEX;
	Scalar fontColor = Scalar(250, 10, 10);
	int fontThickness = 2;

	putText(copiedImg, text, Point(20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

	int pixelHeight = 20;

	// 给定像素的高度，自适应的计算字体大小
	fontScale = getFontScaleFromHeight(fontFace, pixelHeight, fontThickness);
	cout << "fontScale = " << fontScale << endl;

	Mat imageTextFontScale;
	imageTextFontScale = img.clone();
	putText(imageTextFontScale, text, Point(20, 350), fontFace, fontScale, fontColor, fontThickness, LINE_AA);

	imshow("Text written using fontScale",imageTextFontScale);

	// 
	Mat imageGetTextSize;
	imageGetTextSize = img.clone();
	int imageHeight = imageGetTextSize.rows;
	int imageWidth = imageGetTextSize.cols;

	// Get the text box height and width and also the baseLine
	int baseLine = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, fontThickness, &baseLine);
	int textWidth = textSize.width;
	int textHeight = textSize.height;

	cout << "TextWidth = " << textWidth << ", TextHeight = " << textHeight << ", baseLine = " << baseLine << endl;

	// Get the coordinates of text box bottom left corner
	// The xccordinate will be such that the text is centered
	int xcoordinate = (imageWidth - textWidth) / 2;
	// The y coordinate will be such that the entire box is just 10 pixels above the bottom of image
	int ycoordinate = (imageHeight - baseLine - 10);

	cout << "TextBox Bottom Left = (" << xcoordinate << "," << ycoordinate << ")" << endl;

	// Draw the Canvas using a filled rectangle
	Scalar canvasColor = Scalar(255, 255, 255);
	Point canvasBottomLeft(xcoordinate, ycoordinate + baseLine);
	Point canvasTopRight(xcoordinate + textWidth, ycoordinate - textHeight);

	//rectangle(imageGetTextSize, canvasBottomLeft, canvasTopRight, canvasColor, -1);

	cout << "Canvas Bottom Left = " << canvasBottomLeft << ", Top Right = " << canvasTopRight << endl;

	// Now draw the baseline ( just for reference )
	int lineThickness = 2;
	Point lineLeft(xcoordinate, ycoordinate);
	Point lineRight(xcoordinate + textWidth, ycoordinate);
	Scalar lineColor = Scalar(0, 255, 0);

	//line(imageGetTextSize, lineLeft, lineRight, lineColor, lineThickness, LINE_AA);

	// Finally Draw the text
	putText(imageGetTextSize, text, Point(xcoordinate, ycoordinate), fontFace, fontScale, fontColor, fontThickness, LINE_AA);
	imshow("Write image using calculated text size", imageGetTextSize);
	waitKey(0);
	return 0;
}