#include "Paddles.h"

#include <conio.h>

Paddles::Paddles(Board* board)
{
	getLocation(board);

	lPaddleX = origLPaddX;
	lPaddleY = origLPaddY;
	rPaddleX = origRPaddX;
	rPaddleY = origRPaddY;
}

void Paddles::move(Board* board, const Ball* ball, std::string versus)
{

	static char input = '0';
	if (versus == "pvp" || versus == "PVP")
	{
		if (_kbhit())
			input = _getch();
		PVP(board, input);
	}
	else if (versus == "pvc" || versus == "PVC")
	{
		if (_kbhit())
			input = _getch();
		PVC(board, ball, input);
	}
	else
	{
		CVC(board, ball);
	}
}

void Paddles::PVP(Board* board, char input)
{
	if (input == 'w' && board->board[lPaddleY - 1][lPaddleX] != '_' && (board->board[lPaddleY - 1][lPaddleX] != 'O' && board->board[lPaddleY - 1][lPaddleX + 1] != 'O'))
	{
		board->board[lPaddleY - 1][lPaddleX] = '|';
		board->board[lPaddleY - 1][lPaddleX + 1] = '|';
		board->board[lPaddleY + 4][lPaddleX] = ' ';
		board->board[lPaddleY + 4][lPaddleX + 1] = ' ';
		lPaddleY--;
	}
	else if (input == 's' && board->board[lPaddleY + 5][lPaddleX] != '^' && (board->board[lPaddleY + 5][lPaddleX] != 'O' && board->board[lPaddleY + 5][lPaddleX + 1] != 'O'))
	{
		board->board[lPaddleY + 5][lPaddleX] = '|';
		board->board[lPaddleY + 5][lPaddleX + 1] = '|';
		board->board[lPaddleY][lPaddleX] = ' ';
		board->board[lPaddleY][lPaddleX + 1] = ' ';
		lPaddleY++;
	}
	else if (input == 'i' && board->board[rPaddleY - 1][rPaddleX] != '_' && (board->board[rPaddleY - 1][rPaddleX] != 'O' && board->board[rPaddleY - 1][rPaddleX + 1] != 'O'))
	{
		board->board[rPaddleY - 1][rPaddleX] = '|';
		board->board[rPaddleY - 1][rPaddleX + 1] = '|';
		board->board[rPaddleY + 4][rPaddleX] = ' ';
		board->board[rPaddleY + 4][rPaddleX + 1] = ' ';
		rPaddleY--;
	}
	else if (input == 'k' && board->board[rPaddleY + 5][rPaddleX] != '^' && (board->board[rPaddleY + 5][rPaddleX] != 'O' && board->board[rPaddleY + 5][rPaddleX + 1] != 'O'))
	{
		board->board[rPaddleY + 5][rPaddleX] = '|';
		board->board[rPaddleY + 5][rPaddleX + 1] = '|';
		board->board[rPaddleY][rPaddleX] = ' ';
		board->board[rPaddleY][rPaddleX + 1] = ' ';
		rPaddleY++;
	}
}

void Paddles::PVC(Board* board, const Ball* ball, char input)
{
	if (input == 'w' && board->board[lPaddleY - 1][lPaddleX] != '_' && (board->board[lPaddleY - 1][lPaddleX] != 'O' && board->board[lPaddleY - 1][lPaddleX + 1] != 'O'))
	{
		board->board[lPaddleY - 1][lPaddleX] = '|';
		board->board[lPaddleY - 1][lPaddleX + 1] = '|';
		board->board[lPaddleY + 4][lPaddleX] = ' ';
		board->board[lPaddleY + 4][lPaddleX + 1] = ' ';
		lPaddleY--;
	}
	else if (input == 's' && board->board[lPaddleY + 5][lPaddleX] != '^' && (board->board[lPaddleY + 5][lPaddleX] != 'O' && board->board[lPaddleY + 5][lPaddleX + 1] != 'O'))
	{
		board->board[lPaddleY + 5][lPaddleX] = '|';
		board->board[lPaddleY + 5][lPaddleX + 1] = '|';
		board->board[lPaddleY][lPaddleX] = ' ';
		board->board[lPaddleY][lPaddleX + 1] = ' ';
		lPaddleY++;
	}

	if (ball->ballx > (board->board[0].size() / 1.25))
	{
		if (board->board[rPaddleY - 1][rPaddleX] != '_' && (board->board[rPaddleY - 1][rPaddleX] != 'O' && board->board[rPaddleY - 1][rPaddleX + 1] != 'O') && (rPaddleY + 1 > ball->bally))
		{
			board->board[rPaddleY - 1][rPaddleX] = '|';
			board->board[rPaddleY - 1][rPaddleX + 1] = '|';
			board->board[rPaddleY + 4][rPaddleX] = ' ';
			board->board[rPaddleY + 4][rPaddleX + 1] = ' ';
			rPaddleY--;
		}

		else if (board->board[rPaddleY + 5][rPaddleX] != '^' && (board->board[rPaddleY + 5][rPaddleX] != 'O' && board->board[rPaddleY + 5][rPaddleX + 1] != 'O') && (rPaddleY + 3 < ball->bally))
		{
			board->board[rPaddleY + 5][rPaddleX] = '|';
			board->board[rPaddleY + 5][rPaddleX + 1] = '|';
			board->board[rPaddleY][rPaddleX] = ' ';
			board->board[rPaddleY][rPaddleX + 1] = ' ';
			rPaddleY++;
		}
	}
}

void Paddles::CVC(Board* board, const Ball* ball)
{
	if (ball->ballx < (board->board[0].size() / 5.25))
	{
		if (board->board[lPaddleY - 1][lPaddleX] != '_' && (board->board[lPaddleY - 1][lPaddleX] != 'O' && board->board[lPaddleY - 1][lPaddleX + 1] != 'O') && (lPaddleY + 1 > ball->bally))
		{
			board->board[lPaddleY - 1][lPaddleX] = '|';
			board->board[lPaddleY - 1][lPaddleX + 1] = '|';
			board->board[lPaddleY + 4][lPaddleX] = ' ';
			board->board[lPaddleY + 4][lPaddleX + 1] = ' ';
			lPaddleY--;
		}

		else if (board->board[lPaddleY + 5][lPaddleX] != '^' && (board->board[lPaddleY + 5][lPaddleX] != 'O' && board->board[lPaddleY + 5][lPaddleX + 1] != 'O') && (lPaddleY + 3 < ball->bally))
		{
			board->board[lPaddleY + 5][lPaddleX] = '|';
			board->board[lPaddleY + 5][lPaddleX + 1] = '|';
			board->board[lPaddleY][lPaddleX] = ' ';
			board->board[lPaddleY][lPaddleX + 1] = ' ';
			lPaddleY++;
		}
	}

	else if (ball->ballx > (board->board[0].size() / 1.25))
	{
		if (board->board[rPaddleY - 1][rPaddleX] != '_' && (board->board[rPaddleY - 1][rPaddleX] != 'O' && board->board[rPaddleY - 1][rPaddleX + 1] != 'O') && (rPaddleY + 1 > ball->bally))
		{
			board->board[rPaddleY - 1][rPaddleX] = '|';
			board->board[rPaddleY - 1][rPaddleX + 1] = '|';
			board->board[rPaddleY + 4][rPaddleX] = ' ';
			board->board[rPaddleY + 4][rPaddleX + 1] = ' ';
			rPaddleY--;
		}

		else if (board->board[rPaddleY + 5][rPaddleX] != '^' && (board->board[rPaddleY + 5][rPaddleX] != 'O' && board->board[rPaddleY + 5][rPaddleX + 1] != 'O') && (rPaddleY + 3 < ball->bally))
		{
			board->board[rPaddleY + 5][rPaddleX] = '|';
			board->board[rPaddleY + 5][rPaddleX + 1] = '|';
			board->board[rPaddleY][rPaddleX] = ' ';
			board->board[rPaddleY][rPaddleX + 1] = ' ';
			rPaddleY++;
		}
	}
}

void Paddles::getLocation(Board* board)
{
	for (int i = 0; i < board->board.size(); i++)
	{
		for (int j = 0; j < board->board[i].size(); j++)
		{
			if (board->board[i][j] == '|' && board->board[i][j + 1] == '|' && board->board[i][j - 2] == '|')
			{
				origLPaddX = j;
				origLPaddY = i;
			}
			else if (board->board[i][j] == '|' && board->board[i][j + 1] == '|' && board->board[i][j + 3] == '|')
			{
				origRPaddX = j;
				origRPaddY = i;
				return;
			}
		}
	}
}

void Paddles::reset()
{
	lPaddleX = origLPaddX;
	lPaddleY = origLPaddY;

	rPaddleX = origRPaddX;
	rPaddleY = origRPaddY;
}
