#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img = cv::imread("lena.jpg", -1);
	if (img.empty()) return -1;
	cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Example1", img);
	cv::waitKey(0);
	cv::destroyWindow("Example1");
	return 0;
}