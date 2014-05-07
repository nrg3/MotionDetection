#ifndef TECHNIQUES__OPEN_CV_FIRST_MOTION_DETECTOR_H
#define TECHNIQUES__OPEN_CV_FIRST_MOTION_DETECTOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/video.hpp>

#include "MotionDetector.h"
#include "../constants.h"

using namespace cv;

class OpenCVFirstMotionDetector: public MotionDetector {
	Mat previous_frame_;
	Mat motion_map_;
	int threshold_;
	BackgroundSubtractorMOG method;
	Mat fgMask;
public:
	OpenCVFirstMotionDetector ();
	OpenCVFirstMotionDetector (int history, int n_mixtures, 
									double background_ratio, double noise_sigma = 0);

	virtual void process_new_frame(const Mat& frame);
	virtual bool is_motion_at(int x, int y) const;
	virtual const Mat& get_motion_map() const;
};


#endif