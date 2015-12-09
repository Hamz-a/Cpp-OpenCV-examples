#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image, dst;
	Scalar color;
	int x, y, nIntersections = 0;

	if (argc < 2)
	{
		cout << " Usage: " << argv[0] << " image.jpg" << endl;
		return -1;
	}

    // Read image
	image = imread(argv[1], IMREAD_COLOR);
	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find " << argv[1] << std::endl;
		return -1;
	}

	// Apply sobel filter
	Canny(image, dst, 50, 200, 3);

    // Offset to the right
	y = dst.cols - 20;
	for (x = 0; x < dst.rows; x++) {
		// If line found
		if ((int)dst.at<uchar>(x, y) == 255) {
			nIntersections++;
		}

		// Set pixel to 255 (white) to draw a line
		dst.at<uchar>(x, y) = 255;
	}

    // Output result
	cout << argv[1] << ", N intersections: " << nIntersections;
	if (nIntersections >= 8) { // 4 x 2 = 8 lines
		cout << ", the 4 wires are connected" << endl;
	}
	else {
		cout << ", the 4 wires aren't connected" << endl;
	}

    // Some fancy display
	namedWindow("Connector - original", WINDOW_AUTOSIZE)
	imshow("Connector - original", image);

	namedWindow("Connector - Sobel", WINDOW_AUTOSIZE);
	imshow("Connector - Sobel", dst);

	waitKey(0);
	return 0;
}