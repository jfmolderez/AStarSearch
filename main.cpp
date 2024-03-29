#include <algorithm>  // for sort
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// directional deltas
const int delta[4][2] {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::vector<State> ParseLine(std::string line) {
	std::istringstream sline(line);
	int n;
	char c;
	std::vector<State> row;
	while ( sline >> n >> c && c == ',') {
		if ( n== 0 ) {
			row.push_back(State::kEmpty);
		} else {
			row.push_back(State::kObstacle);
		}
	}
	return row;
}

std::vector<std::vector<State>> ReadBoardFile(std::string path) {
	std::ifstream myfile(path);
	std::vector<std::vector<State>> board {};
	if (myfile) {
		std::string line;
		while (getline(myfile, line)) {
			std::vector<State> row = ParseLine(line);
			board.push_back(row);
		}
	}
	return board;
}

/**
 * Compare function for nodes
 */
bool Compare(std::vector<int> n1, std::vector<int> n2) {
	int f1 = n1[2] + n1[3];
	int f2 = n2[2] + n2[3];
	return f1 > f2 ;
}

/**
 * Sort the two-dimensional vector of ints in descending order
 */
void CellSort(std::vector<std::vector<int>> *v) {
	sort(v->begin(), v->end(), Compare);
}

/**
 * Calculate the Manhattan distance
 */
int Heuristic(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) + abs(y2 - y1);
}

/**
 * Check validity of cell
 */
bool CheckValidCell( int x, int y, std::vector<std::vector<State>> & grid) {
	bool on_grid_x = x >= 0 && x < grid.size();
	bool on_grid_y = y >= 0 && y < grid[0].size();
	if ( on_grid_x && on_grid_y ) {
		return grid[x][y] == State::kEmpty;
	}
	return false;
}

void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> & open, std::vector<std::vector<State>> & grid) {
	std::vector<int> node {x, y, g, h};
	open.push_back(node);
	grid[x][y] = State::kClosed;
}

/**
 * Expand current node's neighbors and add them to the open list
 */
void ExpandNeighbors(const std::vector<int> &current, int goal[2], std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>> &grid ) {
	int x = current[0];
	int y = current[1];
	int g = current[2];

	for ( int i = 0; i < 4; i++ ) {
		int x2 = x + delta[i][0];
		int y2 = y + delta[i][1];
	

		if (CheckValidCell(x2, y2, grid)) {
			int g2 = g + 1;
			int h2 = Heuristic(x2, y2, goal[0], goal[1]);
			AddToOpen(x2, y2, g2, h2, openlist, grid);
		}
	}
}

/**
 * Implementation of the A* search algorithm
 */

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int init[2], int goal[2]) {

	// create the vector of open nodes
	std::vector<std::vector<int>> open {};

	// initialize the starting node
	int x = init[0];
	int y = init[1];
	int g = 0;
	int h = Heuristic(x, y, goal[0], goal[1]);
	AddToOpen(x, y, g, h, open, grid);

	while ( open.size() > 0 ) {
		CellSort( &open );
		auto current = open.back();
		open.pop_back();
		int x = current[0];
		int y = current[1];
		grid[x][y] = State::kPath;

		if ( x == goal[0] && y == goal[1]) {
			grid[init[0]][init[1]] = State::kStart;
			grid[x][y] = State::kFinish;
			return grid;
		}
		// If we are not done : expand
		ExpandNeighbors(current, goal, open, grid);

	} // end while loop
	std::cout << "No path found!" << "\n";
	return std::vector<std::vector<State>> {};
}

std::string CellString(State cell) {
	switch( cell ) {
		case State::kObstacle: return "⛰️   ";
    	case State::kPath: return "🚗   ";
    	case State::kStart: return "🚦   ";
    	case State::kFinish: return "🏁   ";		
		default: return "0  ";
	}
}

void PrintBoard(const std::vector<std::vector<State>> board) {
	for( int i = 0; i < board.size(); i++ ) {
		for (int j = 0; j < board[i].size(); j++ ) {
			std::cout << CellString(board[i][j]);
		}
		std::cout << "\n";
	}
}

#include "test.cpp"

int main() {
	int init[2] {0, 0};
	int goal[2] {4, 5};
	auto board = ReadBoardFile("1.board");

	auto solution = Search(board, init, goal);
	PrintBoard(solution);

	// Tests
	TestHeuristic();
	TestAddToOpen();
  	TestCompare();
  	TestSearch();
  	TestCheckValidCell();
  	TestExpandNeighbors();
}
