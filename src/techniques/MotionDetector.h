#ifndef TECHNIQUES__MOTION_DETECTOR_H
#define TECHNIQUES__MOTION_DETECTOR_H

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class MotionDetector {
public:
	virtual void process_new_frame(const Mat& frame) = 0;
	virtual bool is_motion_at(int x, int y) const = 0;
	virtual const Mat& get_motion_map() const = 0;
};


#endif