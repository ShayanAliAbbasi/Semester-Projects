#include "MainGame.h"

#include <conio.h>
#include <iostream>
#include <string>

MainGame::MainGame()
{
	score1 = 0;
	score2 = 0;
	isDone = false;
}

void MainGame::run()
{
	std::string  input;

	std::cout << "\t\t\t\t\tSELECT GAME MODE\n\n";
	std::cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n";
	std::cout << "| Player vs Player (PVP)  | Player vs Computer (PVC)  | Computer vs Computer (CVC)  |\n";
	std::cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n";
	std::cout << "                                         ";

	std::getline(std::cin, input);

	std::cout << "\n\t\t\t\t\tCONTROLS\n\n";
	std::cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n";
	std::cout << "| Left Paddle Up (W)  | Left Paddle Down (S)  | Right Paddle Up (I)  | Right Paddle Down (K)  |\n";
	std::cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n";
	
	std::cout << "\n\t\t\t\t\tTARGET\n\n";
	std::cout << "+ + + + + + + + + + + + +\n";
	std::cout << "| Score " << WIN_SCORE << " points to win |\n";
	std::cout << "+ + + + + + + + + + + + +\n";
	
	std::cout << "\n\t\t\t\t\tPRESS ANY KEY\n\n";
	std::cout << "                                         ";

	_getch();

	gameLoop(input);
	
	std::cin.get();
}

void MainGame::gameLoop(std::string versus)
{
	while (!isDone)
	{
		system("cls");

		board.printBoard();		

		displayScores();

		paddle.move(&board, &ball, versus);

		ball.move(&board);

		checkForPoints();
	}
}

void MainGame::winCheck()
{
	if (score1 == WIN_SCORE)
	{
		system("cls");

		std::cout << "\a\n\n\n\n\n\n\n\n"
			<< "\t\t\t\t _____________\t     \t            __   \n"
			<< "\t\t\t\t|             |\t  /|\t   |  ||\\ ||__  |\n"
			<< "\t\t\t\t|             |\t / |\t   |  || \\| __| |\n"
			<< "\t\t\t\t|             |\t/  |\t   |            |\n"
			<< "\t\t\t\t|             |\t   |\t   |     /\\     |\n"
			<< "\t\t\t\t|_____________|\t   |\t   |    /  \\    |\n"
			<< "\t\t\t\t|              \t   |\t   |   /    \\   |\n"
			<< "\t\t\t\t|              \t   |\t   |  /      \\  |\n"
			<< "\t\t\t\t|              \t   |\t   | /        \\ |\n"
			<< "\t\t\t\t|              \t   |\t   |/          \\|\n\a";

		isDone = true;
	}

	else if (score2 == WIN_SCORE)
	{
		system("cls");

		std::cout << "\a\n\n\n\n\n\n\n\n"
			<< "\t\t\t\t _____________ \t _____________ \t            __   \n"
			<< "\t\t\t\t|             |\t              |\t   |  ||\\ ||__  |\n"
			<< "\t\t\t\t|             |\t              |\t   |  || \\| __| |\n"
			<< "\t\t\t\t|             |\t              |\t   |            |\n"
			<< "\t\t\t\t|             |\t              |\t   |     /\\     |\n"
			<< "\t\t\t\t|_____________|\t _____________|\t   |    /  \\    |\n"
			<< "\t\t\t\t|              \t|              \t   |   /    \\   |\n"
			<< "\t\t\t\t|              \t|              \t   |  /      \\  |\n"
			<< "\t\t\t\t|              \t|              \t   | /        \\ |\n"
			<< "\t\t\t\t|              \t|______________\t   |/          \\|\n\a";

		isDone = true;
	}
}

void MainGame::displayScores()
{
	printf("\t\t\t%d                                                    %d", score1, score2);
}

void MainGame::checkForPoints()
{
	if (ball.ballx - 1 == 0)
	{
		score2++;
		winCheck();

		board.reset();
		ball.reset();
		paddle.reset();

		ball.randomizeDir();

	}

	else if (ball.ballx + 1 == (board.board[ball.bally].size()) - 1)
	{
		score1++;
		winCheck();

		board.reset();
		ball.reset();
		paddle.reset();

		ball.randomizeDir();
	}
}