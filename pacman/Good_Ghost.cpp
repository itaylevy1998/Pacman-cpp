#include "Good_Ghost.h"

void Good_Ghost::UpdateMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board, Pacman& pacman)
{
	
	if (!smart)
	{
		if (_moves == 5)
		{
			_moves = 0;
			smart = true;
			direction = SmartMove(maxRow, maxCol, pacman, board);
		}
		else
		{
			direction = SetMove(maxRow, maxCol, board);
		}
	}
	else
	{
		if (_moves == randMove)
		{
			randMove = RandomizeMove();
			smart = false;
			_moves = 0;
			direction = SetMove(maxRow, maxCol, board);
		}
		else
			direction = SmartMove(maxRow, maxCol, pacman, board);
	}

	Movement(board);
	_moves++;
	
}

Good_Ghost::Good_Ghost()
{
	smart = true;
	randMove = 20;
}

int Good_Ghost::RandomizeMove()
{
	return 19 + rand() % 2;
}
