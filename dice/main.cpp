#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image, image_gray;
	Scalar color;
	size_t i;

	if (argc < 2)
	{
		cout << " Usage: " << argv[0] << " image0.jpg" << endl;
		return -1;
	}

    // Read image
	image = imread(argv[1], IMREAD_COLOR);
	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find " << argv[1] << std::endl;
		return -1;
	}

	// Convert to grayscale
	cvtColor(image, image_gray, CV_BGR2GRAY);

	// Empty vector for our circles
	vector<Vec3f> circles;

	// Apply the Hough Circle Transform algorithm
	HoughCircles(image_gray, circles, CV_HOUGH_GRADIENT, 1, image_gray.rows / 4, 150, 50, 0, 0);

	if (circles.size() > 0) {
		// Output number of pips
		cout << argv[1] << ", found " << circles.size() << " pip(s)." << endl;

		// Draw for fun!
		for (i = 0; i < circles.size(); ++i) {
			Point pip(cvRound(circles[i][0]), cvRound(circles[i][1]));
			circle(image, pip, 3, Scalar(0, 255, 0), -1, 8, 0);
		}
	} else {
		cout << "Couldn't find any pips..." << endl;
	}

	// Show detected pips
	namedWindow("Dice - count pips", CV_WINDOW_AUTOSIZE);
	imshow("Dice - count pips", image);
    
	waitKey(0);
	return 0;
}