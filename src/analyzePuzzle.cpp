#include "analyzePuzzle.h"


tile::tile()
{
	Size s = Size(100, 100);
	Size edge = Size(100, 1);
	Mat tileImg = Mat::zeros(s, CV_8UC3);
	Mat U_edge= Mat::zeros(edge, CV_8UC3);
	Mat D_edge= Mat::zeros(edge, CV_8UC3);
	Mat L_edge= Mat::zeros(edge, CV_8UC3);
	Mat R_edge= Mat::zeros(edge, CV_8UC3);

	w = h = 2;
}
tile::tile(int, int)
{

}
void tile::init(Mat rect)
{
	tileImg = rect.clone();
	imshow("kio", tileImg);
}


analyzePuzzle::analyzePuzzle() :
myPuzzleSolver("", "")
{
	Size s = Size(256, 256);

	Original_img = Mat::zeros(s, CV_8UC3);
	Recomstruct_img = Mat::zeros(s, CV_8UC3);
	puzzle_width = 0;
	puzzle_height = 0;

	string ss = "12,1,3,4;11,2,13,5;15,0,14,6;10,9,8,7;";
	string gg = "1,2,3,4;12,13,14,5;11,0,15,6;10,9,8,7;";

	myPuzzleSolver.initPuzzle(ss);
	myPuzzleSolver.setGoalState(gg);
	//tile my_tile[5][5];
	//for (int i = 0; i < 5; i++)
	//	for (int j = 0; j < 5; j++)
	//	
}
analyzePuzzle::analyzePuzzle(Size s) :
myPuzzleSolver("", "")
{
	Original_img = Mat::zeros(s, CV_8UC3);
	Recomstruct_img = Mat::zeros(s, CV_8UC3);
	puzzle_width = 0;
	puzzle_height = 0;

	string ss = "12,1,3,4;11,2,13,5;15,0,14,6;10,9,8,7;";
	string gg = "1,2,3,4;12,13,14,5;11,0,15,6;10,9,8,7;";

	myPuzzleSolver.initPuzzle(ss);
	myPuzzleSolver.setGoalState(gg);
}
void analyzePuzzle::Init(Size s)
{
	Original_img = Mat::zeros(s, CV_8UC3);
	Recomstruct_img = Mat::zeros(s, CV_8UC3);
	//puzzle_width = 0;
	//puzzle_height = 0;

	string ss = "12,1,3,4;11,2,13,5;15,0,14,6;10,9,8,7;";
	string gg = "1,2,3,4;12,13,14,5;11,0,15,6;10,9,8,7;";

	myPuzzleSolver.initPuzzle(ss);
	myPuzzleSolver.setGoalState(gg);
}
void analyzePuzzle::operator=(const analyzePuzzle &in)
{
}
void analyzePuzzle::ReadSrc(string file)
{
	Original_img = imread(file, CV_LOAD_IMAGE_COLOR);
	//imshow("mjk,", Original_img);
}
void analyzePuzzle::Segmenting()
{
	int w = 2, h = 2;
	int tile_w = Original_img.cols / w, tile_h = Original_img.rows / h;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			cv::Mat image(Original_img);// Transform it into the C++ cv::Mat format
			cv::Rect myROI(j*tile_w, i*tile_w, 150, 150);// Setup a rectangle to define your region of interest
			cv::Mat croppedImage = image(myROI);// Crop the full image to that image contained by the rectangle myROI, Note that this doesn't copy the data

			my_tile[i][j].init(croppedImage);
		}
	}
}
void analyzePuzzle::solve()
{
	ans = myPuzzleSolver.graph_search();

}