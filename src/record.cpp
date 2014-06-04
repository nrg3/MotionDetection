#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <queue>

using namespace cv;
using namespace std;

#include "techniques\NaiveMotionDetector.h"
#include "techniques\OpenCVFirstMotionDetector.h"


time_t get_time() {
	time_t rawtime;
	time (&rawtime);
	return rawtime;
}

string get_time_string(time_t moment) {
	struct tm * timeinfo;
	char buffer[80];

	timeinfo = localtime(&moment);

	strftime(buffer, 80, "%d_%m_%Y__%I_%M_%S",timeinfo);
	std::string str(buffer);
	return str;
}

queue<time_t> times;
queue<Mat> frames;

void save_frame(const Mat& frame, time_t its_time) {
	static int id = 0;
	
	char buffer[80];
	sprintf(buffer, "%08d", id);
	++id;
	
	imwrite(string("recorded_pictures\\") + buffer + "____" + get_time_string(its_time) + ".jpg", frame);
}

void save_queue() {
	while (!frames.empty()) {
		save_frame(frames.front(), times.front());
		frames.pop();
		times.pop();
	}
}

int time_shift = 1;

bool is_important(const Mat& motion_map) {
	int motion = 0;
	for (int i = 0; i < motion_map.rows; ++i) {
		for (int j = 0; j < motion_map.cols; ++j) {
			motion += motion_map.at<bool>(i, j);
		}	
	}	
	
	return motion > 1000000 / 4;
}

int main(int argc, char *argv[]) {

	NaiveMotionDetector naive;
	OpenCVFirstMotionDetector openCVfirst;

	string method_name = "Naive";
	MotionDetector* detector = &naive;

	if (argc == 2 && string(argv[1]) == "OpenCVfirst") {
		detector = &openCVfirst;
		method_name = "OpenCVfirst";
	}
	
	string folderCreateCommand = "mkdir " + string("recorded_pictures");
	system(folderCreateCommand.c_str());

	
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	namedWindow(method_name.c_str(),CV_WINDOW_AUTOSIZE);
	waitKey(100);

	while (1) {
		Mat raw_frame;

		bool success = cap.read(raw_frame);	

		resize(raw_frame, raw_frame, Size(320, 240));

		time_t this_time;
		time(&this_time);

		if (!success) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}	

		while (!times.empty() && this_time - times.front() > time_shift) {
			times.pop();
			frames.pop();
		}

		times.push(this_time);
		frames.push(raw_frame);

		Mat frame = raw_frame.clone();
		detector->process_new_frame(raw_frame);
		
		if (is_important(detector->get_motion_map()))  {
			save_queue();
			circle(frame, Point(10, 10), 10, Scalar(0, 0, 255, 0), -1);
		}

		imshow(method_name.c_str(), frame);

		if (waitKey(100) == 27) {
				cout << "esc key is pressed by user" << endl;
				break; 
		}
	}

	return 0;	
}