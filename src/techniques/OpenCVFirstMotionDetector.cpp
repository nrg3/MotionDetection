#include "OpenCVFirstMotionDetector.h"
#include <math.h>

OpenCVFirstMotionDetector::OpenCVFirstMotionDetector() {		
}

OpenCVFirstMotionDetector::OpenCVFirstMotionDetector(int history, int n_mixtures, 
														double background_ratio, double noise_sigma)
		: method(history, n_mixtures, background_ratio, noise_sigma)  {
}

void OpenCVFirstMotionDetector::process_new_frame(const Mat& frame) {
	method(frame, fgMask, 0.01); 
}

bool OpenCVFirstMotionDetector::is_motion_at(int x, int y) const {
	return fgMask.at<bool>(x, y);
}

const Mat& OpenCVFirstMotionDetector::get_motion_map() const {
	return fgMask;
}

OpenCVFirstMotionDetector::~OpenCVFirstMotionDetector() {
}