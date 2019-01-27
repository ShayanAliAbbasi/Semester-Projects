#include "Ball.h"

#include <random>
#include <time.h>

std::default_random_engine random(time(NULL));
std::uniform_int_distribution<int> Random(0, 5);
std::uniform_int_distribution<int> RandomR(0, 2);
std::uniform_int_distribution<int> RandomL(3, 5);

enum BallDirection { R, RDT, RDD, L, LDT, LDD };

Ball::Ball(Board* board)
{
	_direction = Random(random);

	getLocation(board);

	ballx = origx;
	bally = origy;
}

void Ball::move(Board* board)
{
	getDirection(board);

	switch (_direction)
	{
	case R:
		board->board[bally][ballx] = ' ';
		board->board[bally][++ballx] = 'O';
		break;
	case RDT:
		board->board[bally][ballx] = ' ';
		board->board[--bally][++ballx] = 'O';
		break;
	case RDD:
		board->board[bally][ballx] = ' ';
		board->board[++bally][++ballx] = 'O';
		break;
	case L:
		board->board[bally][ballx] = ' ';
		board->board[bally][--ballx] = 'O';
		break;
	case LDT:
		board->board[bally][ballx] = ' ';
		board->board[--bally][--ballx] = 'O';
		break;

	case LDD:
		board->board[bally][ballx] = ' ';
		board->board[++bally][--ballx] = 'O';
		break;
	}
}

void Ball::getDirection(Board* board)
{
	if (board->board[bally][ballx + 1] == '|' && _direction == R)
	{
		_direction = RandomL(random);
	}
	else if (board->board[bally][ballx + 1] == '|' && _direction == RDD)
	{
		_direction = RandomL(random);
	}
	else if (board->board[bally][ballx + 1] == '|' && _direction == RDT)
	{
		_direction = RandomL(random);
	}
	else if (board->board[bally][ballx - 1] == '|' && _direction == L)
	{
		_direction = RandomR(random);
	}
	else if (board->board[bally][ballx - 1] == '|' && _direction == LDD)
	{
		_direction = RandomR(random);
	}
	else if (board->board[bally][ballx - 1] == '|' && _direction == LDT)
	{
		_direction = RandomR(random);
	}
	else if (board->board[bally - 1][ballx] == '_' && _direction == RDT)
	{
		_direction = RDD;
	}
	else if (board->board[bally - 1][ballx] == '_' && _direction == LDT)
	{
		_direction = LDD;
	}
	else if (board->board[bally + 1][ballx] == '^' && _direction == LDD)
	{
		_direction = LDT;
	}
	else if (board->board[bally + 1][ballx] == '^' && _direction == RDD)
	{
		_direction = RDT;
	}
}

void Ball::randomizeDir()
{
	_direction = Random(random);
}

void Ball::getLocation(Board* board)
{
	for (int i = 0; i < board->board.size(); i++)
	{
		for (int j = 0; j < board->board[i].size(); j++)
		{
			if (board->board[i][j] == 'O')
			{
				origx = j;
				origy = i;
				return;
			}
		}
	}
}

void Ball::reset()
{
	ballx = origx;
	bally = origy;
}