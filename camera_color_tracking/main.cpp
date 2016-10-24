#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
    // Open default camera
    VideoCapture cap(0);

    // Check if camera is available
    if(!cap.isOpened())
    {
        return -1;
    }


    Mat processed, frame;
    namedWindow("original", WINDOW_AUTOSIZE);
    namedWindow("processed", WINDOW_AUTOSIZE);
    int posX = 0, posY = 0;
    double m01, m10, area;

    while(1)
    {
        // Get a new frame from camera
        cap >> frame;

        // Convert to HSV
        cvtColor(frame, processed, COLOR_BGR2HSV_FULL);

        // Filter red
        inRange(processed, Scalar(0, 70, 50), Scalar(10, 255, 255), processed);

        // Calculate the moments
        Moments oMoments = moments(processed);
        m01 = oMoments.m01;
        m10 = oMoments.m10;
        area = oMoments.m00;

        // Filter position
        if (area > 1000000) {
            // Position
            posX = m10 / area;
            posY = m01 / area;

            // Draw a green point
            circle(frame, Point(posX, posY), 5, Scalar(0, 255, 0), 10);
        }

        imshow("original", frame);
        imshow("processed", processed);

        // Break it
        if(waitKey(30) >= 0)
        {
            break;
        }
    }

    return 0;
}
