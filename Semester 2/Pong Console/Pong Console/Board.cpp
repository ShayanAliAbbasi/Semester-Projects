#include "Board.h"

#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>

Board::Board()
{
	std::string boardLines;
	std::ifstream getBoard("board.txt");

	if (getBoard.fail())
	{
		perror("board.txt");
		exit(1);
	}

	while(getline(getBoard, boardLines))
	{
		board.emplace_back(boardLines);
	}
	
	getBoard.close();

	origBoard = board;
}

void Board::printBoard()
{
	for (int i = 0; i < board.size(); i++)
	{
		printf("\t\t%s\n", board[i].c_str());
	}
}

void Board::reset()
{
	board = origBoard;
}




