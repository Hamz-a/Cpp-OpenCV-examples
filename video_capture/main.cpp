#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
    // open the default camera
    VideoCapture cap(0);
    
    // check if we succeeded
    if(!cap.isOpened()) {
        std::cout << "Fix your camera!" << std::endl;
        return -1;
    }

    Mat frame;
    namedWindow("video", WINDOW_AUTOSIZE);
    
    while(1)
    {
        // Get a new frame from camera
        cap >> frame;

        // Show the frame
        imshow("video", frame);
        
        // Exit
        if(waitKey(30) >= 0) break;
    }

    return 0;
}