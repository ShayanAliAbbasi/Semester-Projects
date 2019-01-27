#pragma once
#include <vector>

class Board
{
public:
	Board();
	void printBoard();
	void reset();

	std::vector<std::string> board;
private:
	std::vector<std::string> origBoard;
};

