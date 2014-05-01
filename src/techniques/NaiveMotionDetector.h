#ifndef TECHNIQUES__NAIVE_MOTION_DETECTOR_H
#define TECHNIQUES__NAIVE_MOTION_DETECTOR_H

#include <opencv2/highgui/highgui.hpp>
#include "MotionDetector.h"
#include "../constants.h"

using namespace cv;

class NaiveMotionDetector: public MotionDetector {
	Mat previous_frame_;
	Mat motion_map_;
	int threshold_;
public:
	NaiveMotionDetector ();
	NaiveMotionDetector (int theshold);

	virtual void process_new_frame(const Mat& frame);
	virtual bool is_motion_at(int x, int y) const;
	virtual const Mat& get_motion_map() const;
};


#endif