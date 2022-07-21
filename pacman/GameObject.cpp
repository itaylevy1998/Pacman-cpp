#include "GameObject.h"
#include <vector>
void GameObject::SetPosition(const int row, const int col)
{
	_pos.SetRow(row);
	_pos.SetCol(col);
}

void GameObject::SetLoadDirection(const Direction& _direction)
{
	direction = _direction;
}

void GameObject::SetNumMoves(int numMoves)
{
	_moves = numMoves;
}

int GameObject::getMoves() const
{
	return _moves;
}

void GameObject::updateMoves()
{
	_moves += 1;
}

bool GameObject::CheckWall(const int& row, const int& col, const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board)
{
	if (row == maxRow || row == -1)
		return true;
	if (col == maxCol || col == -1)
		return true;
	if (board[row][col].getSignpiece() == WALL)
		return true;
	return false;
}

bool GameObject::CheckTunnel(const int& row, const int& col ,const int& maxRow,const int& maxCol, vector<vector<GameBoard>>& board)
{
	if (row == 0)
	{
		if (board[maxRow - 1][col].getSignpiece() != WALL)
			return true;
		else
			return false;
	}
	else if (row == (maxRow - 1))
	{
		if (board[0][col].getSignpiece() != WALL)
			return true;
		else
			return false;
	}
	else if (col == 0)
	{
		if (board[row][maxCol - 1].getSignpiece() != WALL)
			return true;
		else
			return false;
	}
	else if (col == (maxCol - 1))
	{
		if (board[row][0].getSignpiece() != WALL)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool GameObject::Obstacle(const int& row, const int& col, const int& maxRow, const int& maxCol ,vector<vector<GameBoard>>& board, Direction direction)
{
	switch (direction)
	{
	case Direction::Up : if (CheckWall(row - 1, col, maxRow, maxCol,board) || CheckTunnel(row - 1, col,maxRow, maxCol, board))
		return true;
		break;
	case Direction::Down: if (CheckWall(row + 1, col, maxRow, maxCol, board) || CheckTunnel(row + 1, col, maxRow, maxCol, board))
		return true;
		break;
	case Direction::Left: if (CheckWall(row, col - 1, maxRow, maxCol, board) || CheckTunnel(row, col - 1, maxRow, maxCol, board))
		return true;
		break;
	case Direction::Right: if (CheckWall(row, col + 1, maxRow, maxCol, board) || CheckTunnel(row, col + 1, maxRow, maxCol, board))
		return true;
		break;
	}
	return false;
}

Direction GameObject::SetMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board)
{
	int random_move, row = _pos.getRow(), col = _pos.getCol();
	while (true)
	{
		random_move = rand() % 4;
		switch (random_move)
		{
		case (int)Direction::Up: if (!Obstacle(row, col, maxRow, maxCol, board, Direction::Up))
		{
			return Direction::Up;
		}
				 break;
		case (int)Direction::Down: if (!Obstacle(row, col, maxRow, maxCol, board, Direction::Down))
		{
			return Direction::Down;
		}
				   break;
		case (int)Direction::Left: if (!Obstacle(row, col, maxRow, maxCol, board, Direction::Left))
		{
			return Direction::Left;
		}
				   break;
		case (int)Direction::Right: if (!Obstacle(row, col, maxRow, maxCol, board, Direction::Right))
		{
			return Direction::Right;
		}
					break;
		default:
			break;
		}
	}


}

void GameObject::Movement(vector<vector<GameBoard>>& board, bool silent)
{
	int row = _pos.getRow(), col = _pos.getCol();

	switch (direction)
	{
	case Direction::Up: SetPosition(row - 1, col);
		if(!silent)
			board[row][col].printPiece(row, col);
		break;
	case Direction::Down: SetPosition(row + 1, col);
		if (!silent)
			board[row][col].printPiece(row, col);
		break;
	case Direction::Left: SetPosition(row, col - 1);
		if (!silent)
			board[row][col].printPiece(row, col);
		break;
	case Direction::Right: SetPosition(row, col + 1);
		if (!silent)
			board[row][col].printPiece(row, col);
		break;
	default:
		break;
	}
}

void GameObject::setStartPosition(const int& row, const int& col)
{
	_pos.SetCol(col);
	_pos.SetRow(row);
	_startPos.SetCol(col);
	_startPos.SetRow(row);
}

Direction GameObject::getDirection() const
{
	return direction;
}

int GameObject::getStartRow() const
{
	return _startPos.getRow();
}

int GameObject::getStartCol() const
{
	return _startPos.getCol();
}


int GameObject::getRow() const
{
	return _pos.getRow();
}

int GameObject::getCol() const
{
	return _pos.getCol();
}

