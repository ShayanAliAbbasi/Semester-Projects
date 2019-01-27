#pragma once

#include "Board.h"

class Ball
{
public:
	Ball(Board* board);
	void move(Board* board);
	void getDirection(Board* board);
	void randomizeDir();
	void getLocation(Board* board);
	void reset();

	int ballx;
	int bally;

private:
	int _direction ;
	int origx;
	int origy;
};

