#include <opencv2/opencv.hpp>
#include "puzzle.h"

using namespace cv;
using namespace std;

class tile
{
public:
	tile();
	tile(int, int);
	void init(Mat rect);
	Mat tileImg;

	Mat U_edge;
	Mat D_edge;
	Mat L_edge;
	Mat R_edge;

	tile *U_tile;
	tile *D_tile;
	tile *L_tile;
	tile *R_tile;

	int w_pixels;
	int h_pixels;
};

class analyzePuzzle
{
public:
	analyzePuzzle();
	analyzePuzzle(Size);
	void Init(Size);
	void operator=(const analyzePuzzle &in);
	void ReadSrc(string);
	void Segmenting();
	double matching(tile&, tile&, int relation);// return macthing rate (0.0 ~ 1.0), relateion 1:top-down, 2-down-top, 3-left-right, 4-right-left
	void solve();
	

	Mat Original_img;    // input img
	Mat Recomstruct_img; // analyzed reconstruct img
	tile my_tile[5][5];
	int puzzle_width;
	int puzzle_height;

	puzzleSolver myPuzzleSolver;	
	puzzle ans;
};