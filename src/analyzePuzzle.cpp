#include "analyzePuzzle.h"


tile::tile()
{
	Size s = Size(100, 100);
	Size edge = Size(100, 1);

	tileImg = Mat::zeros(s, CV_8UC3);
	U_edge= Mat::zeros(edge, CV_8UC1);
	D_edge= Mat::zeros(edge, CV_8UC1);
	L_edge= Mat::zeros(edge, CV_8UC1);
	R_edge= Mat::zeros(edge, CV_8UC1);

	w_pixels = h_pixels = 0;
}
tile::tile(int, int)
{
	Size s = Size(100, 100);
	Size edge = Size(100, 1);

	tileImg = Mat::zeros(s, CV_8UC3);
	U_edge = Mat::zeros(edge, CV_8UC1);
	D_edge = Mat::zeros(edge, CV_8UC1);
	L_edge = Mat::zeros(edge, CV_8UC1);
	R_edge = Mat::zeros(edge, CV_8UC1);

	w_pixels = h_pixels = 0;
}
void tile::init(Mat rect)
{
	Size s = Size(100, 100);
	Size edge = Size(100, 1);

	tileImg = Mat::zeros(s, CV_8UC3);
	U_edge = Mat::zeros(edge, CV_8UC1);
	D_edge = Mat::zeros(edge, CV_8UC1);
	L_edge = Mat::zeros(edge, CV_8UC1);
	R_edge = Mat::zeros(edge, CV_8UC1);

	w_pixels = tileImg.cols / 2;
	h_pixels = tileImg.rows / 2;

	Mat tmp;
	tileImg = rect.clone();
	tileImg.convertTo(tmp, CV_8UC1);

	for (int i = 0; i < w_pixels; i++)
	{
		U_edge.at<uchar>(0, i) = tmp.at<uchar>(0, i);			   // Top edge
		D_edge.at<uchar>(0, i) = tmp.at<uchar>(tileImg.rows - 1, i);// Buttom edge
		L_edge.at<uchar>(0, i) = tmp.at<uchar>(i, 0);			   // Left edge
		R_edge.at<uchar>(0, i) = tmp.at<uchar>(i, tileImg.cols - 1);// Right edge
	}
	//imshow("l;p", U_edge);

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
			cv::Rect myROI(j*tile_w, i*tile_w, tile_w, tile_h);// Setup a rectangle to define your region of interest
			cv::Mat croppedImage = image(myROI);// Crop the full image to that image contained by the rectangle myROI, Note that this doesn't copy the data

			my_tile[i][j].init(croppedImage);
		//imshow("po;",my_tile[i][j].tileImg);
		}
	}

}
double analyzePuzzle::matching(tile& first, tile& second, int relation)
{
	double match_rate = 0;

	switch (relation)
	{
	case 1:// top-down
		for (int i = 0; i < first.U_edge.cols; i++)
		{
			match_rate += abs(my_tile[1][0].U_edge.at<uchar>(0, i) - my_tile[0][1].D_edge.at<uchar>(0, i)) / 255.0;
		}
		match_rate = 1.0-(match_rate / 100.0);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
	return match_rate;
}

void analyzePuzzle::solve()
{
	ans = myPuzzleSolver.graph_search();
	//return matching(my_tile[0][1], my_tile[1][0], 1);

}