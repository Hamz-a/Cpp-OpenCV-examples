#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>
#include "iostream"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image, dst;

	if (argc < 2)
	{
		cout << " Usage: " << argv[0] << " image0.jpg" << endl;
		return -1;
	}

	// Read image as grayscale
	image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find " << argv[1] << std::endl;
		return -1;
	}

	// Denoise
	fastNlMeansDenoising(image, dst, 7, 21);

	namedWindow("Noise reduction - original", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Noise reduction - original", image); // Show our image inside it.

	namedWindow("Noise reduction - reduced", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Noise reduction - reduced", dst); // Show our image inside it.

	waitKey(0);
	return 0;
}