#include "analyzePuzzle.h"

analyzePuzzle::analyzePuzzle() 
{
}
analyzePuzzle::analyzePuzzle(Size s) 
{
	Original_img = Mat::zeros(s, CV_8UC3);
	Recomstruct_img = Mat::zeros(s, CV_8UC3);
}
void analyzePuzzle::Init(Size)
{
}
void analyzePuzzle::operator=(const analyzePuzzle &in)
{
}
void analyzePuzzle::ReadSrc(string file)
{
	Original_img = imread(file, CV_LOAD_IMAGE_COLOR);
	imshow("mjk,", Original_img);

}