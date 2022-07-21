#include "GameBoard.h"


GameBoard::GameBoard()
{
	_sign = 0;
}

GameBoard::~GameBoard()
{
}

void GameBoard::setGamePiece(const char ch)
{
	_sign = ch;
}

void GameBoard::printPiece(const int& x, const int& y) const
{
			gotoxy(x, y);
			if (Color)
			{
				if (_sign == WALL)
					cout << GRAY << _sign << RESET;
				else
					cout << FOODCOLOR<< _sign << RESET;
			}
			else
				cout << _sign;
}


char GameBoard::getSignpiece() const
{
	return _sign;
}
