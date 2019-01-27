#pragma once

#include "Board.h"
#include "Ball.h"
#include "Paddles.h"

const int WIN_SCORE = 5;

class MainGame
{
public:
	MainGame();
	void run();
	void gameLoop(std::string versus);
	void winCheck();
	void checkForPoints();
	void displayScores();
	
private:
	int score1;
	int score2;
	bool isDone;

	Board board;
	Paddles paddle = Paddles(&board);
	Ball ball = Ball(&board);
};

