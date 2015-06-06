#include "../include/analyzePuzzle.h"


tile::tile()
{
	Size s = Size(150, 150); ////////////////////////////////////////////
	Size edge = Size(150, 1);////////////////////////////////////////////

	init(Mat::zeros(s, CV_8UC3), 0);
}
void tile::operator= (const tile &in)
{
	this->tileImg = in.tileImg.clone();

	this->U_edge = in.U_edge;
	this->D_edge = in.D_edge;
	this->L_edge = in.L_edge;
	this->R_edge = in.R_edge;

	this->w_pixels = in.tileImg.cols;
	this->h_pixels = in.tileImg.rows;

	this->U_tile = in.U_tile;
	this->D_tile = in.D_tile;
	this->L_tile = in.L_tile;
	this->R_tile = in.R_tile;

	this->U_matching_rate = in.U_matching_rate;
	this->D_matching_rate = in.D_matching_rate;
	this->L_matching_rate = in.L_matching_rate;
	this->R_matching_rate = in.R_matching_rate;

	this->isBlank = in.isBlank;
	this->linked =in.linked;
	this->Max_links = in.Max_links;
	this->isFullLinked = in.isFullLinked;

	this->debug_num = in.debug_num;

}
void tile::init(Mat rect, int debug_num)
{
	Size s = Size(150, 150);////////////////////
	Size edge = Size(150, 1);////////////////////////////

	tileImg = Mat::zeros(s, CV_8UC1);
	U_edge = Mat::zeros(edge, CV_8UC1);
	D_edge = Mat::zeros(edge, CV_8UC1);
	L_edge = Mat::zeros(edge, CV_8UC1);
	R_edge = Mat::zeros(edge, CV_8UC1);

	w_pixels = tileImg.cols ;
	h_pixels = tileImg.rows ;

	U_tile = NULL;
	D_tile = NULL;
	L_tile = NULL;
	R_tile = NULL;

	U_matching_rate = 0;
	D_matching_rate = 0;
	L_matching_rate = 0;
	R_matching_rate = 0;

	//Mat tmp;
	tileImg = rect.clone();
	//tileImg.convertTo(tileImg, CV_8UC1, 255);

	////Mat tileImg_gray;
	//Mat grad;
	//int scale = 1;
	//int delta = 0;
	//int ddepth = CV_16S;
	//GaussianBlur(tileImg, tileImg, Size(9,9), 0, 0, BORDER_DEFAULT);
	///// Generate grad_x and grad_y
	//Mat grad_x, grad_y;
	//Mat abs_grad_x, abs_grad_y;
	///// Gradient X
	////Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	//Sobel(tileImg, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	//convertScaleAbs(grad_x, abs_grad_x);
	///// Gradient Y
	////Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	//Sobel(tileImg, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//convertScaleAbs(grad_y, abs_grad_y);
	///// Total Gradient (approximate)
	//addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, tileImg);

	//Top edge
	U_edge = tileImg(Rect(0, 0, 150, 1)).clone();
	//Buttom edge
	D_edge = tileImg(Rect(0, 149, 150, 1)).clone();
	//Left edge
	transpose(tileImg(Rect(0, 0, 1, 150)).clone(), L_edge);
	//Right edge
	transpose(tileImg(Rect(149, 0, 1, 150)).clone(), R_edge);

	//imshow("U", U_edge);
	//imshow("D", D_edge);
	//imshow("L", L_edge);
	//imshow("R", R_edge);

	isBlank = false;
	linked = 0;
	Max_links = 4;///////////////////////////////////////////////////
	isFullLinked = false;

	this->debug_num = debug_num;
}
void tile::linking(tile& t, int relation, double rate)
{
	switch (relation)
	{
	case 1:// top-down
		if (this->D_matching_rate < rate)
		{
			this->D_tile = &t;
			this->D_tile->U_tile = this;
			this->D_matching_rate = this->D_tile->U_matching_rate = rate;

			this->linked++;
			this->D_tile->linked++;
			if (this->linked == this->Max_links) this->isFullLinked = true;
			if (this->D_tile->linked == Max_links) this->D_tile->isFullLinked = true;
		}
		break;
	case 2:// down-top
		if (this->U_matching_rate < rate)
		{
			this->U_tile = &t;
			this->U_tile->D_tile = this;
			this->U_matching_rate = this->U_tile->D_matching_rate = rate;

			this->linked++;
			this->U_tile->linked++;
			if (this->linked == this->Max_links) this->isFullLinked = true;
			if (this->U_tile->linked == Max_links) this->U_tile->isFullLinked = true;
		}
		break;
	case 3:// left-right
		if (this->R_matching_rate < rate)
		{
			this->R_tile = &t;
			this->R_tile->L_tile = this;
			this->R_matching_rate = this->R_tile->L_matching_rate = rate;

			this->linked++;
			this->R_tile->linked++;
			if (this->linked == this->Max_links) this->isFullLinked = true;
			if (this->R_tile->linked == Max_links) this->R_tile->isFullLinked = true;
		}
		break;
	case 4:// right-left
		if (this->L_matching_rate < rate)
		{
			this->L_tile = &t;
			this->L_tile->R_tile = this;
			this->L_matching_rate = this->L_tile->R_matching_rate = rate;

			this->linked++;
			this->L_tile->linked++;
			if (this->linked == this->Max_links) this->isFullLinked = true;
			if (this->L_tile->linked == Max_links) this->L_tile->isFullLinked = true;
		}
		break;
	default:
		break;
	}

}

analyzePuzzle::analyzePuzzle() 
{
	Size s = Size(256, 256);
	Init(s);
}
analyzePuzzle::analyzePuzzle(Size s)
{
	Init(s);
}
void analyzePuzzle::Init(Size s)
{
	Original_img = Mat::zeros(s, CV_8UC3);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			my_tile[i][j].init(Mat::zeros(Size(150, 150), CV_8UC1), 0);
		}
	}
	imgLoaded = false;
}
void analyzePuzzle::ReadSrc(string file)
{
	Init(Size(256, 256));

	Original_img = imread(file, CV_LOAD_IMAGE_COLOR);
	imgLoaded = true;

	puzzle_width = Original_img.cols / 150;///////////////////////////
	puzzle_height = Original_img.rows / 150;////////////////////////////////
	//imshow("mjk,", Original_img);
}
string analyzePuzzle::Segmenting()
{
	int tile_w = Original_img.cols / puzzle_width, tile_h = Original_img.rows / puzzle_height;
	std::stringstream buffer;

	for (int i = 0; i < puzzle_height; i++)
	{
		for (int j = 0; j < puzzle_width; j++)
		{
			cv::Mat image = Original_img.clone();// Transform it into the C++ cv::Mat format
			image.convertTo(image, CV_8UC1);
			cv::Rect myROI(j*tile_w, i*tile_w, tile_w, tile_h);// Setup a rectangle to define your region of interest
			cv::Mat croppedImage = image(myROI);// Crop the full image to that image contained by the rectangle myROI, Note that this doesn't copy the data

			//const int debug_num_for_test3[4] = { 2, 4, 1, 3 };

			Mat tmp;
			absdiff(croppedImage, Scalar::all(255), tmp);
			double s = sum(tmp)[0];
			if (sum(tmp)[0] < 1000.0) // check if it is blank tile
			{
				my_tile[i][j].init(croppedImage, 0);
				buffer << "0";
				my_tile[i][j].isBlank = true;
			}
			else 
			{ 
				my_tile[i][j].init(croppedImage, puzzle_width * i + j + 1);
				buffer << puzzle_width * i + j + 1;
			}

			if (j < puzzle_width - 1) buffer << ',';
		}
		buffer << ';';
	}

	return buffer.str();
	//myPuzzleSolver.initPuzzle(startState);
}
double analyzePuzzle::matching(tile& first, tile& second, int relation)
{
	double match_rate = 0;

	//imshow("f-D", first.D_edge);
	//imshow("s-U", second.U_edge);
	Mat tmp; 
	switch (relation)
	{
		case 1:// topTile:downTile
			absdiff(first.D_edge, second.U_edge, tmp);
			match_rate = sum(tmp)[0];
			break;
		case 2:// down-top
			absdiff(first.U_edge, second.D_edge, tmp);
			match_rate = sum(tmp)[0];
			break;
		case 3:// left-right
			absdiff(first.R_edge, second.L_edge, tmp);
			match_rate = sum(tmp)[0];
			break;
		case 4:// right-left
			absdiff(first.L_edge, second.R_edge, tmp);
			match_rate = sum(tmp)[0];
			//match_rate += abs(first.L_edge.at<uchar>(0, i) - second.R_edge.at<uchar>(0, i)) / 255.0;
			break;
		default:
			break;
	}

	match_rate /= 255;
	return 1.0-(match_rate / 150.0);////////////////////////////////////
}

void analyzePuzzle::solve()
{
	for (int outer_row = 0; outer_row < puzzle_height; outer_row++)
	{
		for (int outer_col = 0; outer_col < puzzle_width; outer_col++)
		{
			if (my_tile[outer_row][outer_col].isBlank) { continue; }
			// matching relation between outer-tile and inner-tile
			for (int relation = 1; relation <= 4; relation++)
			{
				double matching_rate = 0;
				int best_row = 0, best_col = 0;

				for (int row = 0; row < puzzle_height; row++)
				{
					for (int col = 0; col < puzzle_width; col++)
					{
						if (my_tile[row][col].isBlank) { continue; }
						if (outer_col == col && outer_row == row) { continue; }

						double new_matching_rate = matching(my_tile[outer_row][outer_col], my_tile[row][col], relation);
						if (matching_rate < new_matching_rate)
						{
							matching_rate = new_matching_rate;
							best_row = row;
							best_col = col;
						}
					}
				}	

				if (matching_rate > 0.95)
				{
					my_tile[outer_row][outer_col].linking(my_tile[best_row][best_col], relation, matching_rate);
				}
			}
		}
	}

}

string analyzePuzzle::generateGoalState()
{
	tile* UL_ptr;
	// get initial position
	for (int i = 0; i < puzzle_height; i++)
	{
		for (int j = 0; j < puzzle_width; j++)
		{
			if (&(my_tile[i][j]) != NULL)
			{
				UL_ptr = &(my_tile[i][j]);
				break;
			}
		}
		if (UL_ptr != NULL) { break; }
	}

	// triverse to upper-left tile
	while ((UL_ptr->L_tile != NULL) || (UL_ptr->U_tile != NULL))
	{
		while (UL_ptr->U_tile != NULL)
		{
			UL_ptr = UL_ptr->U_tile;
		}
		if (UL_ptr->L_tile != NULL) { UL_ptr = UL_ptr->L_tile; }
	}
	//imshow("Upper-Left tile", UL_ptr->tileImg);

	std::stringstream buffer;
	int x = 0, y = 0;
	int col = 0, row = 0;
	// Link blank-tiles into relation, and generate goal-stat string
	while (y < puzzle_height)
	{
		tile* ptr = UL_ptr;
		for (int i = 0; i < y; i++) 
		{ 
			if (ptr->D_tile == NULL && y < puzzle_height )
			{
				getFirstBlankTile(col, row);
				ptr->linking(my_tile[row][col], 1, 2.0);
				ptr->R_tile->D_tile->linking(my_tile[row][col], 4, 2.0);
				if (puzzle_height - 1 - y > 1)
				{
					ptr->R_tile->D_tile->D_tile->L_tile->linking(my_tile[row][col], 2, 2.0);
				}
			}
			ptr = ptr->D_tile; 
		}
		while (x < puzzle_width)
		{
			buffer << ptr->debug_num;// << ",";
			if (x < puzzle_width - 1) { buffer << ','; }
			if (ptr->R_tile == NULL && x < puzzle_width - 1)
			{ 
				getFirstBlankTile(col, row);
				ptr->linking(my_tile[row][col], 3, 2.0);

				if (puzzle_width - 1 - x > 1)
				{
					if (puzzle_height - y > 1)
						ptr->U_tile->R_tile->R_tile->D_tile->linking(my_tile[row][col], 4, 2.0);
					else
						ptr->D_tile->R_tile->R_tile->U_tile->linking(my_tile[row][col], 4, 2.0);
				}
			}
			ptr = ptr->R_tile;
			x++;
		}
		y++;
		x = 0;
		buffer << ";";
	}
	return buffer.str();
}

void analyzePuzzle::getFirstBlankTile(int& col, int& row)
{
	for (int r = 0; r < puzzle_height; r++)
	{
		for (int c = 0; c < puzzle_width; c++)
		{
			if (my_tile[r][c].isBlank && my_tile[r][c].linked == 0)
			{
				col = c;
				row = r;
				//my_tile[r][c].isBlank = false;
				return;
			}
		}
	}
	col = -1;
	row = -1;
}

string analyzePuzzle::debug_printRelations()
{
	std::stringstream buffer;

	for (int row = 0; row < puzzle_height; row++)
	{
		for (int col = 0; col < puzzle_width; col++)
		{
			if (my_tile[row][col].U_tile != NULL) { buffer << my_tile[row][col].debug_num << " U " << my_tile[row][col].U_tile->debug_num << " " << my_tile[row][col].U_matching_rate << '\n'; }
			if (my_tile[row][col].D_tile != NULL) { buffer << my_tile[row][col].debug_num << " D " << my_tile[row][col].D_tile->debug_num << " " << my_tile[row][col].D_matching_rate << '\n'; }
			if (my_tile[row][col].L_tile != NULL) { buffer << my_tile[row][col].debug_num << " L " << my_tile[row][col].L_tile->debug_num << " " << my_tile[row][col].L_matching_rate << '\n'; }
			if (my_tile[row][col].R_tile != NULL) { buffer << my_tile[row][col].debug_num << " R " << my_tile[row][col].R_tile->debug_num << " " << my_tile[row][col].R_matching_rate << '\n'; }
		}
	}

	return buffer.str();
}
