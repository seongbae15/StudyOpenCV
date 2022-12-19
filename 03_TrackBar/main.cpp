#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int slider_position = 0;
//int run = 1;
bool runMode = true;
bool stepMode = true;
int dontset = 0;

cv::VideoCapture cap;

void onTrackbarSlide(int pos, void*);

int main() {
	cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
	cap.open("Open222part480.mp4");
	int frames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video's Frame : "<< frames<< ", " << "Width : " << tmpw << ", Height : " << tmph << endl;

	cv::createTrackbar("Position", "Example", &slider_position, frames, onTrackbarSlide);

	cv::Mat frame;

	while (true) {
		//if (run != 0)
		if (runMode) {
			cap >> frame;
			if (frame.empty()) break;

			int currentPos = (int)cap.get(cv::CAP_PROP_POS_FRAMES);
			dontset = 1;

			cv::setTrackbarPos("Position", "Example", currentPos);
			cv::imshow("Example", frame);

			//run -= 1;
			if (stepMode) {
				runMode = false;
			}
		}
		char c = (char)cv::waitKey(10);
		if (c == 's') {
			//run = 1;
			stepMode = true;
			runMode = true;
			cout << "Single Step = " << stepMode << endl;
		}
		if (c == 'r') {
			//run = -1;
			runMode = true;
			stepMode = false;
			cout << "Run mode = " << runMode << endl;
		}
		if (c == 27)
			break;
	}

	return 0;
}

void onTrackbarSlide(int pos, void*) {
	if (!dontset) {
		//int run = 1;
		stepMode = true;
		runMode = true;
		cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	}
	dontset = 0;
}

// 주석처리 된 변수 int type run을 boolean 타입 2개의 변수로 확장해서 사용.
// 비디오가 Run mode 재생 시, 변수 run 값이 계속 작아짐. 언더플로우 예방을 위해서, boolean 타입 스위치 동작으로 변경.