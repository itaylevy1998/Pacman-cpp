#include "PacmanClass.h"


Pacman::Pacman(const int row, const int col, const int score, const int Lives, const Direction _direction)
{
	_pos.SetRow(row);
	_pos.SetCol(col);
	_score = score;
	_remaininglives = Lives;
	direction = direction;
}

Pacman::~Pacman()
{
}

void Pacman::setPacmanPosition()
{
	if (direction == Direction::Left)
		_pos.SetCol(_pos.getCol() - 1);
	else if (direction == Direction::Right)
		_pos.SetCol(_pos.getCol() + 1);
	else if (direction == Direction::Up)
		_pos.SetRow(_pos.getRow() - 1);
	else if (direction == Direction::Down)
		_pos.SetRow(_pos.getRow() + 1);
	else
		return;
	
	
}


void Pacman::setPacmanScore(int bonus)
{
	_score = _score + bonus;
}

void Pacman::setPacmanLives(int minus)
{
	_remaininglives = _remaininglives - minus;
}

void Pacman::setPacmanDirection(const char& _direction)
{
	if (_direction == LEFT || _direction == (LEFTA))
		direction = Direction::Left;
	else if (_direction == RIGHT || _direction == (RIGHTD))
		direction = Direction::Right;
	else if (_direction == UP || _direction == (UPW))
		direction = Direction::Up;
	else if (_direction == DOWN || _direction == (DOWNX))
		direction = Direction::Down;
	else if (_direction == STAY || _direction == (STAYS))
		direction = Direction::Stay;
}

void Pacman::setPacmanIfTunnel(const int row, const int col)
{
	_pos.SetRow(row);
	_pos.SetCol(col);
}

void Pacman::resetPacmanScore(const int& StartScore)
{
	_score = StartScore;
}

void Pacman::resetPacmanLives(const int& StartLives)
{
	_remaininglives = StartLives;
}

void Pacman::printPacman() const
{
	gotoxy(_pos.getRow(),_pos.getCol());
	if (Color)
	{
		cout << YELLOW << Pacman_sign << RESET;
	}
	else
		cout << Pacman_sign;
}

int Pacman::getPacmanScore() const
{
	return _score;
}

int Pacman::getPacmanLives() const
{
	return _remaininglives;
}

void Pacman::ResetPos()
{
	_pos.SetRow(getStartRow());
	_pos.SetCol(getStartCol());
}


bool Pacman::CheckIfPacmanHitWall(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board)
{
	
	if (direction == Direction::Up)
	{
		return CheckWall(_pos.getRow() - 1, _pos.getCol(), maxRow, maxCol, board);
	}
	else if (direction == Direction::Down)
	{
		return CheckWall(_pos.getRow() + 1, _pos.getCol(), maxRow, maxCol, board);
	}
	else if (direction == Direction::Left)
	{
		return CheckWall(_pos.getRow(), _pos.getCol() - 1, maxRow, maxCol, board);
	}
	else if (direction == Direction::Right)
	{
		return CheckWall(_pos.getRow(), _pos.getCol() + 1, maxRow, maxCol, board);
	}
	else
		return false;
}

bool Pacman::CheckTunnel(const int& maxRow,const int& maxCol, vector<vector<GameBoard>>& board)
{
	if (_pos.getRow() == 0 && direction == Direction::Up)
	{
		if (board[maxRow - 1][_pos.getCol()].getSignpiece() != WALL)
		{
			setPacmanIfTunnel(maxRow - 1, _pos.getCol());
			return true;
		}
		else
			return false;
	}
	else if (_pos.getRow() == (maxRow - 1) && direction == Direction::Down)
	{
		if (board[0][_pos.getCol()].getSignpiece() != WALL)
		{
			setPacmanIfTunnel(0, _pos.getCol());
			return true;
		}
		else
			return false;
	}
	else if (_pos.getCol() == 0 && direction == Direction::Left)
	{
		if (board[_pos.getRow()][maxCol - 1].getSignpiece() != WALL)
		{
			setPacmanIfTunnel(_pos.getRow(), maxCol - 1);
			return true;
		}
		else
			return false;
	}
	else if (_pos.getCol() == (maxCol - 1) && direction == Direction::Right)
	{
		if (board[_pos.getRow()][0].getSignpiece() != WALL)
		{
			setPacmanIfTunnel(_pos.getRow(), 0);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}