#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#include "techniques\NaiveMotionDetector.h"
#include "techniques\OpenCVFirstMotionDetector.h"


int main(int argc, char *argv[]) {

	NaiveMotionDetector naive;
	OpenCVFirstMotionDetector openCVfirst;

	string method_name = "Naive";
	MotionDetector* detector = &naive;

	if (argc == 2 && string(argv[1]) == "OpenCVfirst") {
		detector = &openCVfirst;
		method_name = "OpenCVfirst";
	}

	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	namedWindow(method_name.c_str(),CV_WINDOW_AUTOSIZE);

	while (1) {
		Mat raw_frame;

		bool success = cap.read(raw_frame);
		Mat frame(raw_frame);	

		if (!success) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		detector->process_new_frame(raw_frame);
		
		int cid = 0;
		for (int i = 0; i < frame.rows; ++i) {
			for (int j = 0; j < frame.cols; ++j) {
				if (detector->is_motion_at(i, j)) {
					frame.at<Vec3b>(i,j)[0] = 0;
					frame.at<Vec3b>(i,j)[1] = 0;
					frame.at<Vec3b>(i,j)[2] = 255; 
				}
			}
		}

		imshow(method_name.c_str(), frame);

		if (waitKey(15) == 27) {
				cout << "esc key is pressed by user" << endl;
				break; 
		}
	}
	return 0;	
}