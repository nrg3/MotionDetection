#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); // open the video camera no. 0

	  if (!cap.isOpened())  // if not success, exit program
			{
		cout << "Cannot open the video cam" << endl;
				return -1;
			}

		   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
		   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

			cout << "Frame size : " << dWidth << " x " << dHeight << endl;

			namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

			waitKey(100);

			while (1)
			{
				Mat frame;

				bool bSuccess = cap.read(frame); // read a new frame from video

			if (!bSuccess) //if not success, break loop
			{
			cout << "Cannot read a frame from video stream" << endl;
			break;
			}

			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					frame.at<Vec3b>(i,j)[0] = 0;
					frame.at<Vec3b>(i,j)[1] = 0;
					frame.at<Vec3b>(i,j)[2] = 255; 
				}
			}

				imshow("MyVideo", frame); //show the frame in "MyVideo" window

				if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
		cout << "esc key is pressed by user" << endl;
		break; 
		}
			}
			return 0;

		




    Mat im = imread("D:/pic.JPG");
    if (im.empty()) 
    {
        cout << "Cannot load image!" << endl;
        return -1;
    }
    imshow("Image", im);
    waitKey(0);
}