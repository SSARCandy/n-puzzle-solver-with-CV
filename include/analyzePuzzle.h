#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class analyzePuzzle
{
public:
	analyzePuzzle();
	analyzePuzzle(Size);
	void Init(Size);
	void operator=(const analyzePuzzle &in);
	void ReadSrc(string);

	Mat Original_img;    // input img
	Mat Recomstruct_img; // analyzed reconstruct img

};