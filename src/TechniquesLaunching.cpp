#include "TechniquesLaunching.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include <opencv2/highgui/highgui.hpp>
using namespace cv;

void launch_method(MotionDetector* detector, const string& path, int groundtruth_id, const string& path_to) {
	std::ostringstream stream;
	
	string folderCreateCommand = "mkdir -p " + path + "\\" + path_to;
	system(folderCreateCommand.c_str());

	for (int id = 0; id <= groundtruth_id; ++id) {	
		stream << path << "\\b" << std::setw(5) << std::setfill('0') << id << ".bmp";
		string file_path = stream.str();
		stream.str("");
		stream.clear();

		Mat frame = imread(file_path, 1);
		detector->process_new_frame(frame);
		
		stream << path << "\\" << path_to << "\\b" << std::setw(5) << std::setfill('0') << id << ".bmp";
		string output_path = stream.str();
		stream.str("");
		stream.clear();
		
		imwrite(output_path, detector->get_motion_map());
	}
}