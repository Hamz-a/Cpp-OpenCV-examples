#include <opencv2/opencv.hpp>

int main(int, char**)
{
    // Open default camera
    cv::VideoCapture cap(0);

    // Camera working?
    if(!cap.isOpened()) {
        std::cout << "Fix your camera!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("video", cv::WINDOW_AUTOSIZE);

    while(1)
    {
        // Get a new frame from camera
        cap >> frame;

        // Show the frame
        imshow("video", frame);

        // Exit
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;
}