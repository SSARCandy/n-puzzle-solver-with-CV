#include "puzzle.h"

puzzle::puzzle()
{
	width = 0;
	height = 0;
	Score = 0;
	steps = 0;
	MDscore = 999;
	actCount = 0;

	for (int i = 0; i < MAX_STACKS; i++)
		action[i] = "";
}
puzzle::puzzle(int arr[][MAX_HEIGHT_AND_WIDTH], int w, int h)
{
	width = w;
	height = h;
	Score = 0;
	steps = 0;
	MDscore = 999;
	actCount = 0;

	copyState(state, arr);
	for (int i = 0; i < MAX_STACKS; i++)
		action[i] = "";
}
puzzle &puzzle::operator= (const puzzle & other)
{
	MDscore = other.MDscore;
	width = other.width;
	height = other.height;
	Score = other.Score;
	steps = other.steps;
	actCount = other.actCount;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			state[i][j] = other.state[i][j];

	for (int i = 0; i < other.actCount; i++)
		action[i] = other.action[i];

	return *this;
}
void puzzle::copyState(int dest[][MAX_HEIGHT_AND_WIDTH], int source[][MAX_HEIGHT_AND_WIDTH])
{
	stringstream buffer;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dest[i][j] = source[i][j];
		}
	}
}
bool puzzle::swap(int w, int h, int act)
{
	//action: 1-up, 2-down, 3-left, 4-right
	stringstream buffer;
	switch (act)
	{
	case 1://UP
		if (h - 1 >= 0)
		{
			if (state[h - 1][w] != -1 && state[h - 1][w] != 0)
			{
				int tmp = state[h - 1][w];
				state[h - 1][w] = state[h][w];
				state[h][w] = tmp;
				buffer << "(" << w + 1 << ", " << h + 1 << ", U)" << endl;
				action[actCount++] = buffer.str();
				return true;
			}
			return false;
		}
		return false;

		break;
	case 2://DOWN
		if (h + 1 < height)
		{
			if (state[h + 1][w] != -1 && state[h + 1][w] != 0)
			{
				int tmp = state[h + 1][w];
				state[h + 1][w] = state[h][w];
				state[h][w] = tmp;
				buffer << "(" << w + 1 << ", " << h + 1 << ", D)" << endl;
				action[actCount++] = buffer.str();
				return true;
			}
			return false;
		}
		return false;
		break;
	case 3://LEFT
		if (w - 1 >= 0)
		{
			if (state[h][w - 1] != -1 && state[h][w - 1] != 0)
			{
				int tmp = state[h][w - 1];
				state[h][w - 1] = state[h][w];
				state[h][w] = tmp;
				buffer << "(" << w + 1 << ", " << h + 1 << ", L)" << endl;
				action[actCount++] = buffer.str();
				return true;
			}
			return false;
		}
		return false;
		break;
	case 4://RIGHT
		if (w + 1 < width)
		{
			if (state[h][w + 1] != -1 && state[h][w + 1] != 0)
			{
				int tmp = state[h][w + 1];
				state[h][w + 1] = state[h][w];
				state[h][w] = tmp;
				buffer << "(" << w + 1 << ", " << h + 1 << ", R)" << endl;
				action[actCount++] = buffer.str();
				return true;
			}
			return false;
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}
void puzzle::printCurrentState()
{
	cout << "|---------Current State----------|" << " MD: " << MDscore << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout.width(2);
			cout << state[i][j] << ' ';
		}
		cout << endl;
	}
}
void puzzle::setScore(int md, int steps)
{
	MDscore = md;
	Score = md + steps;
}
int puzzle::getMDscore()
{
	return MDscore;
}

puzzleSolver::puzzleSolver(string start, string goal)
{
	spaces = 0;
	if (start != "" && goal != "")
	{
		initPuzzle(start);
		setGoalState(goal);
		startState.setScore(ManhattenDistance(startState), 0);
		goalState.setScore(ManhattenDistance(goalState), 0);
	}
}
void puzzleSolver::initPuzzle(string ss)
{
	int tmpArray[MAX_HEIGHT_AND_WIDTH][MAX_HEIGHT_AND_WIDTH];
	string s = ss;
	int w = 0, h = 0;

	/*--------�B�zstart State data & �����e��-----------*/
	while (s.find(';') != string::npos)
	{
		h++;
		s.replace(s.find(';'), 1, ",");
	}
	while (s.find(',') != string::npos)
	{
		w++;
		s.replace(s.find(','), 1, " ");
	}

	height = h;
	width = (w / h);

	stringstream streamSS(s);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			streamSS >> tmpArray[i][j];
		}
	}
	//count spaces
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (tmpArray[i][j] == 0)
				spaces++;

	startState = puzzle(tmpArray, width, height);
}
void puzzleSolver::setGoalState(string goal)
{
	int tmpArray[MAX_HEIGHT_AND_WIDTH][MAX_HEIGHT_AND_WIDTH];
	string s = goal;
	int w = 0, h = 0;

	/*--------�B�zgoal State data-------------*/
	while (s.find(';') != string::npos)
	{
		h++;
		s.replace(s.find(';'), 1, ",");
	}while (s.find(',') != string::npos)
	{
		w++;
		s.replace(s.find(','), 1, " ");
	}

	if (h != height || (w / h) != width)
	{
		cout << "illegal goal State" << endl;
		return;
	}

	stringstream stream(s);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			stream >> tmpArray[i][j];
		}
	}
	goalState = puzzle(tmpArray, width, height);
}
bool puzzleSolver::goalTest(puzzle p)
{
	if (p.getMDscore() == 0)
		return true;
	else
		return false;
}
bool puzzleSolver::isSame(int a[][MAX_HEIGHT_AND_WIDTH], int b[][MAX_HEIGHT_AND_WIDTH])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (a[i][j] != b[i][j])
				return false;
		}
	}
	return true;
}
int  puzzleSolver::MD_one_instence(puzzle p, int h, int w)
{
	//find the min distance to goal state
	int GoalState_h = 0, GoalState_w = 0;
	while (true)
	{
		if (p.state[h][w] == goalState.state[GoalState_h][GoalState_w])
		{
			return abs(h - GoalState_h) + abs(w - GoalState_w);
		}
		else
		{
			if (GoalState_w < width)
			{
				GoalState_w++;
			}
			else
			{
				GoalState_h++;
				GoalState_w = 0;
			}
		}
	}
}
int  puzzleSolver::ManhattenDistance(puzzle p)
{
	int score = 0;
	for (int CurState_h = 0; CurState_h < height; CurState_h++)
	{
		for (int CurState_w = 0; CurState_w < width; CurState_w++)
		{
			// not block or space
			if (p.state[CurState_h][CurState_w] != 0 && p.state[CurState_h][CurState_w] != -1)
			{
				score += MD_one_instence(p, CurState_h, CurState_w);
			}
		}
	}
	return score;
}
int  puzzleSolver::findIndexOf(int target, puzzle p, int position)
{
	int pos = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (target == p.state[i][j])
			{
				if (pos == position)
					return i*width + j;
				pos++;
			}
		}
	}
	return -1;
}
bool puzzleSolver::swap(puzzle p, int w, int h, int action)
{
	//action: 1-up, 2-down, 3-left, 4-right
	switch (action)
	{
	case 1://UP
		if (h - 1 >= 0)
		{
			if (p.state[h - 1][w] != -1 && p.state[h - 1][w] != 0)
			{
				int tmp = p.state[h - 1][w];
				p.state[h - 1][w] = p.state[h][w];
				p.state[h][w] = tmp;
				//				cout << "---(" << w + 1 << ", " << h + 1 << ", U)" << endl;
				return true;
			}
			return false;
		}
		return false;
		break;
	case 2://DOWN
		if (h + 1 < height)
		{
			if (p.state[h + 1][w] != -1 && p.state[h + 1][w] != 0)
			{
				int tmp = p.state[h + 1][w];
				p.state[h + 1][w] = p.state[h][w];
				p.state[h][w] = tmp;
				//				cout << "---(" << w + 1 << ", " << h + 1 << ", D)" << endl;
				return true;
			}
			return false;
		}
		return false;
		break;
	case 3://LEFT
		if (w - 1 >= 0)
		{
			if (p.state[h][w - 1] != -1 && p.state[h][w - 1] != 0)
			{
				int tmp = p.state[h][w - 1];
				p.state[h][w - 1] = p.state[h][w];
				p.state[h][w] = tmp;
				//				cout << "---(" << w + 1 << ", " << h + 1 << ", L)" << endl;
				return true;
			}
			return false;
		}
		return false;
		break;
	case 4://RIGHT
		if (w + 1 < width)
		{
			if (p.state[h][w + 1] != -1 && p.state[h][w + 1] != 0)
			{
				int tmp = p.state[h][w + 1];
				p.state[h][w + 1] = p.state[h][w];
				p.state[h][w] = tmp;
				//				cout << "---(" << w + 1 << ", " << h + 1 << ", R)" << endl;
				return true;
			}
			return false;
		}
		return false;
		break;
	default:
		return false;
		break;
	}
}
void puzzleSolver::expandNode(list<puzzle> &frontier, puzzle node)
{
	puzzle tmp_puzzle;
	for (int space_counter = 0; space_counter < spaces; space_counter++)
	{
		int w = findIndexOf(0, node, space_counter) % width;
		int h = findIndexOf(0, node, space_counter) / width;

		// try u, d, l, r and compute score
		for (int action = 1; action <= 4; action++)
		{
			tmp_puzzle = node;
			if (tmp_puzzle.swap(w, h, action))
			{
				tmp_puzzle.setScore(ManhattenDistance(tmp_puzzle), ++tmp_puzzle.steps);
				InsertFrontier(frontier, tmp_puzzle);
			}
		}
	}
}
void puzzleSolver::InsertFrontier(list<puzzle> &f, puzzle &t)
{
	std::list<puzzle>::iterator it;
	if (f.size() == 0)
		f.push_back(t);
	for (it = f.end();;)
	{
		it--;
		if (it == f.begin())
		{
			f.insert(f.begin(), t);
			break;
		}
		if (t.Score <= (*it).Score)
		{
			std::list<puzzle>::iterator tmp = it;
			if (tmp++ == f.end())
			{
				f.push_back(t);
				break;
			}
			f.insert(tmp, t);
			break;
		}
	}

}
puzzle puzzleSolver::graph_search()
{
	puzzle node;
	list<puzzle> explored;
	int search_nodes = 0;

	frontier.clear();
	frontier.push_back(startState);

	while (true)
	{
		if (frontier.size() != 0)
		{
			node = frontier.back();
			frontier.pop_back();

			if (goalTest(node))
			{
				return node;
			}
			else
			{
				bool had_explored = false;
				for (std::list<puzzle>::iterator it = explored.begin(); it != explored.end(); it++)
				{
					if (isSame((*it).state, node.state))
					{
						had_explored = true;
						break;
					}
				}
				if (!had_explored)
				{
					search_nodes++;
					explored.push_back(node);
					expandNode(frontier, node);
				}
			}
		}
		else
			return goalState;// failure
	}
}
