#include "Fruit.h"


Fruit::Fruit()
{
	_scoreNum = 5 + rand() % 4;
	_appear = false;
	_moves = 0;
	_movesAppear = 1;
	direction = (Direction)(rand() % 4);
}

void Fruit::setStartPos(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board)
{
	int row=0, col=0;
	do
	{
		row = rand() % maxRow;
		col = rand() % maxCol;
	} while (CheckWall(row, col, maxRow, maxCol, board) || CheckTunnel(row, col, maxRow, maxCol, board));
	_pos.SetRow(row);
	_pos.SetCol(col);
}



void Fruit::setScore()
{
	_scoreNum = 5 + rand() % 4;
}

void Fruit::setScore(int num)
{
	_scoreNum = num;
}

void Fruit::setAppear()
{
	_appear = !_appear;
}

void Fruit::updateStatus(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board, ofstream& stepFile, bool IsSave)
{
	
	_moves++;
	if (_appear)
	{
		if (_moves >= MovesDisappear)
		{
			_moves = 0;
			setAppear();
			setMovesAppear();
			if(IsSave)
				stepFile << "F2 " << _pos.getRow() << ' ' << _pos.getCol() << endl;
			board[_pos.getRow()][_pos.getCol()].printPiece(_pos.getRow(), _pos.getCol());
			return;
		}
		else
		{
			if (Obstacle(_pos.getRow(),_pos.getCol(),maxRow, maxCol, board, direction))
			{
				direction = SetMove(maxRow, maxCol, board);
			}
			Movement(board);
		}
		Print();
		if(IsSave)
		{
			stepFile << "F1 " << (int)direction << endl;
		}
	}
	else
	{
		if (_moves >= _movesAppear)
		{
			setStartPos(maxRow, maxCol, board);
			setAppear();
			setScore();
			if(IsSave)
			{
				stepFile << "F0 " << (int)direction << ' ' << _pos.getRow() << ' ' << _pos.getCol() << ' ' << getScore() << endl;
			}
			_moves = 0;
			direction = SetMove(maxRow, maxCol, board);
		}
		
	}
}

void Fruit::setMovesAppear()
{
	_movesAppear = 4 + rand() % 6;
}

void Fruit::Eaten()
{
	_moves = 0;
	_appear = false;
	setMovesAppear();

}


bool Fruit::checkAppear() const
{
	return _appear;
}

int Fruit::getScore() const
{
	return _scoreNum;
}

void Fruit::Print() const
{
	gotoxy(_pos.getRow(), _pos.getCol());
	cout << _scoreNum;
}
