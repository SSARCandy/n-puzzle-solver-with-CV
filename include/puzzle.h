#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <list>

#define MAX_HEIGHT_AND_WIDTH 10
#define MAX_STACKS 100
using namespace std;

class puzzle{
public:
	puzzle();
	puzzle(int arr[][MAX_HEIGHT_AND_WIDTH], int w, int h);
	puzzle &operator= (const puzzle & other);
	void copyState(int dest[][MAX_HEIGHT_AND_WIDTH], int source[][MAX_HEIGHT_AND_WIDTH]);
	
	bool swap(int w, int h, int act);// return true if the swap action is success.
	void printCurrentState();
	void setScore(int md, int steps);
	int getMDscore();

	int steps;
	int Score;
	int state[MAX_HEIGHT_AND_WIDTH][MAX_HEIGHT_AND_WIDTH];
	int actCount;
	string action[MAX_STACKS];
private:
	int MDscore;
	int width;
	int height;
};

class puzzleSolver{
public:
	puzzleSolver(string start, string goal);
	void initPuzzle(string ss);
	void setGoalState(string goal);
	bool goalTest(puzzle p);
	bool isSame(int a[][MAX_HEIGHT_AND_WIDTH], int b[][MAX_HEIGHT_AND_WIDTH]);
	int MD_one_instence(puzzle p, int h, int w);
	int ManhattenDistance(puzzle p);//Manhatten distance heuristic
	int findIndexOf(int target, puzzle p, int position);//return one int = i + j*width
	bool swap(puzzle p, int w, int h, int action);// return true if the swap action is success.
	void expandNode(list<puzzle> &frontier, puzzle node);
	void InsertFrontier(list<puzzle> &f, puzzle &t);
	puzzle graph_search();

private:
	list<puzzle>frontier;
	puzzle startState, goalState;
	int width;
	int height;
	int spaces;
};

