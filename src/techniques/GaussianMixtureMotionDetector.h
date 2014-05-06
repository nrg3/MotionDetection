#ifndef TECHNIQUES__GAUSSIAN_MIXTURE_MOTION_DETECTOR_H
#define TECHNIQUES__GAUSSIAN_MIXTURE_MOTION_DETECTOR_H

/*
Based on code from https://github.com/safeng/Background-Modeling Copyright (C) 2012 Shuang Feng
*/

#include <opencv2/highgui/highgui.hpp>
#include "MotionDetector.h"
#include "../constants.h"

using namespace cv;

class GaussianMixtureMotionDetector: public MotionDetector {
	Mat previous_frame_;
	Mat motion_map_;
	int threshold_;
public:
	GaussianMixtureMotionDetector ();
	GaussianMixtureMotionDetector (int theshold);

	virtual void process_new_frame(const Mat& frame);
	virtual bool is_motion_at(int x, int y) const;
	virtual const Mat& get_motion_map() const;
};


#endif