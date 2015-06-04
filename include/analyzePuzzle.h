#include <opencv2/opencv.hpp>
#include "puzzle.h"

using namespace cv;
using namespace std;

class tile
{
public:
	tile();
	tile(int, int);
	void operator=(const tile &in);
	void init(Mat rect, int debug_num);
	void linking(tile& t, int relation, double rate);
	//void linking(int relation, double rate);
	Mat tileImg;

	Mat U_edge;
	Mat D_edge;
	Mat L_edge;
	Mat R_edge;

	tile *U_tile;
	tile *D_tile;
	tile *L_tile;
	tile *R_tile;

	double U_matching_rate;
	double D_matching_rate;
	double L_matching_rate;
	double R_matching_rate;

	int linked; // how many links this tile have
	int Max_links; // maximun links this tile can has
	bool isFullLinked;

	int w_pixels;
	int h_pixels;

	bool isBlank;
	int debug_num;
};

class analyzePuzzle
{
public:
	analyzePuzzle();
	analyzePuzzle(Size);
	void Init(Size);
	//void operator=(const analyzePuzzle &in);
	void ReadSrc(string);
	// Cut Input image into tiles
	void Segmenting();
	// Return macthing rate (0.0 ~ 1.0), relateion 1:top-down, 2:down-top, 3:left-right, 4:right-left
	double matching(tile&, tile&, int relation);
	
	void getFirstBlankTile(int& col, int& row);
	// Generate goal-state string
	void generateGoalState();
	void solve();
	string debug_printRelations();
	
	bool imgLoaded;
	Mat Original_img;    // input img
	Mat Recomstruct_img; // analyzed reconstruct img
	tile my_tile[5][5];
	int puzzle_width;
	int puzzle_height;

	string startState;
	string goalState;
	puzzleSolver myPuzzleSolver;	
	puzzle ans;
};