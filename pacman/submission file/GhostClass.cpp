#include "GhostClass.h"


Ghost::Ghost()
{
	_pos.SetRow(0);
	_pos.SetCol(0);
	move_counter = 0;
	direction = GhostDirection(rand() % 4);
}

Ghost::~Ghost()
{

}


void Ghost::SetPosition(const int x, const int y)
{
	_pos.SetRow(x);
	_pos.SetCol(y);
}



void Ghost::Print()
{
	gotoxy(_pos.getRow(), _pos.getCol());
	if (Color)
	{
		cout << CYAN << "$" << RESET;
	}
	else
		cout << "$";

}


void Ghost::UpdateMove(GameBoard board[][SizeCol])
{
	if (move_counter == 20 || GhostObstacle(_pos.getRow(), _pos.getCol(), board, direction))
	{
		direction = SetMove(board);
		move_counter = 0;
	}
	
	Movement(board);
	move_counter++;
}


GhostDirection Ghost::SetMove(GameBoard board[][SizeCol])
{
	int random_move, row = _pos.getRow(), col = _pos.getCol(); 
	while(true)
	{
		random_move = rand() % 4;
		switch (random_move)
		{
		case Up_G: if (!GhostObstacle(row, col, board, Up_G))
		{
			return Up_G;
		}
				 break;
		case Down_G: if (!GhostObstacle(row, col, board, Down_G))
		{
			return Down_G;
		}
				 break;
		case Left_G: if (!GhostObstacle(row, col, board, Left_G))
		{
			return Left_G;
		}
				 break;
		case Right_G: if (!GhostObstacle(row, col, board, Right_G))
		{
			return Right_G;
		}
				  break;
		default:
			break;
		}
	}
	
	
}

/*update the ghost position and prints the position of the older board piece it has overwritten*/
void Ghost::Movement(GameBoard board[][SizeCol])
{
	int row = _pos.getRow(), col = _pos.getCol();

	switch (direction)
	{
	case Up_G: SetPosition(row - 1, col);
		board[row][col].printPiece(row, col);
		break;
	case Down_G: SetPosition(row + 1, col);
		board[row][col].printPiece(row, col);
		break;
	case Left_G: SetPosition(row, col - 1);
		board[row][col].printPiece(row, col);
		break;
	case Right_G: SetPosition(row, col + 1);
		board[row][col].printPiece(row, col);
		break;
	default: 
		break;
	}
}

int Ghost::getGhostRow()
{
	return _pos.getRow();
}

int Ghost::getGhostCol()
{
	return _pos.getCol();
}

GhostDirection Ghost::GetDirection()
{
	return direction;
}

bool Ghost::GhostObstacle(const int& row, const int& col, GameBoard board[][SizeCol], GhostDirection direction) const
{
	switch (direction)
	{
	case Up_G: if (Game::CheckWall(row - 1, col, board) || Game::CheckTunnel(row - 1, col, board))
		return true;
		break;
	case Down_G: if (Game::CheckWall(row + 1, col, board) || Game::CheckTunnel(row+1, col, board))
		return true;
		break;
	case Left_G: if (Game::CheckWall(row, col - 1, board) || Game::CheckTunnel(row, col - 1, board))
		return true;
		break;
	case Right_G: if (Game::CheckWall(row, col + 1, board) || Game::CheckTunnel(row, col + 1, board))
		return true;
		break;
	}	
	return false;
}
