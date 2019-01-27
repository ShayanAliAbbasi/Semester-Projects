#pragma once

#include "Board.h"
#include "Ball.h"

class Paddles
{
public:
	Paddles(Board* board);
	void move(Board* board, const Ball* ball, std::string versus);
	void getLocation(Board* board);
	void reset();

private:
	void PVP(Board* board, char input);
	void PVC(Board* board, const Ball* ball, char input);
	void CVC(Board* board, const Ball* ball);

	int lPaddleX;
	int lPaddleY;
	int rPaddleX;
	int rPaddleY;

	int origLPaddX;
	int origLPaddY;
	int origRPaddX;
	int origRPaddY;

};

