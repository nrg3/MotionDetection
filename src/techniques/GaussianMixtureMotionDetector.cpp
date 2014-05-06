#include "GaussianMixtureMotionDetector.h"
#include <math.h>

GaussianMixtureMotionDetector::GaussianMixtureMotionDetector() 
	: threshold_(20) {
}

NaiveMotionDetector::NaiveMotionDetector(int threshold) 
	: threshold_(threshold) {
}

void NaiveMotionDetector::process_new_frame(const Mat& frame) {
	if (motion_map_.rows == 0) {
		motion_map_.create(frame.rows, frame.cols, CV_8UC1);
	}

	const uchar* previous_pixels = static_cast<const uchar*>(previous_frame_.data);
	int cn = previous_frame_.channels();
	int cols = previous_frame_.cols;
	int rows = previous_frame_.rows;

	const uchar* current_pixels = static_cast<const uchar*>(frame.data);

	for (int row = 0; row < rows; ++row) {
		for (int column = 0; column < cols; ++column) {
			size_t shift = row * cols * cn + column * cn;
			if (abs(previous_pixels[shift + 0] -
					current_pixels[shift + 0]) > threshold_ || // Blue
					abs(previous_pixels[shift + 1] -
					current_pixels[shift + 1]) > threshold_ || // Green
					abs(previous_pixels[shift + 2] -           
					current_pixels[shift + 2]) > threshold_) { // Red
				motion_map_.at<uchar>(row, column) = 1;
			} else {
				motion_map_.at<uchar>(row, column) = 0;
			}
		}
	}
	previous_frame_ = frame.clone();
}

bool NaiveMotionDetector::is_motion_at(int x, int y) const {
	if (motion_map_.at<uchar>(x, y) == 1) {
		return true;
	} else {
		return false;
	}
}

const Mat& NaiveMotionDetector::get_motion_map() const {
	return motion_map_;
}