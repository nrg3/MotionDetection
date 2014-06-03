#include "MethodScore.h"
#include <sstream>
#include <iomanip>

#include <opencv2/highgui/highgui.hpp>
using namespace cv;


Score calculate_score(const Mat& result, const Mat& detector_result) {	
	int true_positives = 0, false_positives = 0, 
		true_negatives = 0, false_negatives = 0;

	for (int row = 0; row < result.rows; ++row) {
		for (int column = 0; column < result.cols; ++column) {
			bool is_real_foreground = result.at<bool>(row, column);
			bool is_foreground = detector_result.at<bool>(row, column);

			if (is_real_foreground) {
				if (is_foreground) {
					++true_positives;
				} else {
					++false_negatives;
				}
			} else {
				if (is_foreground) {
					++false_positives;
				} else {
					++true_negatives;
				}
			}
		}
	}

	return Score(true_positives, false_positives,
				 true_negatives, false_negatives);
}




Score get_score_on_pics_sequence(MotionDetector* detector, const string& path, int groundtruth_id) {
	std::ostringstream stream;

	for (int id = 0; id <= groundtruth_id; ++id) {	
		stream << path << "\\b" << std::setw(5) << std::setfill('0') << id << ".bmp";
		string file_path = stream.str();
		stream.str("");
		stream.clear();

		Mat frame = imread(file_path, 1);
		detector->process_new_frame(frame);
	}

	stream << path << "\\hand_segmented_" << 
						std::setw(5) << std::setfill('0') << groundtruth_id << ".bmp";
	string result_path = stream.str();
	stream.str("");
	stream.clear();

	Mat result = imread(result_path, CV_LOAD_IMAGE_GRAYSCALE) > 128;
	Mat detector_result = detector->get_motion_map();

	return calculate_score(result, detector_result);
}