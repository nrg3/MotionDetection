#ifndef SCORE__METHOD_SCORE_H
#define SCORE__METHOD_SCORE_H

#include "../techniques/MotionDetector.h"
#include "Score.h"
#include <string>
using std::string;

Score get_score_on_pics_sequence(MotionDetector* detector, const string& path, int groundtruth_id);

#endif
