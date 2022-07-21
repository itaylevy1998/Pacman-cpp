#include "GhostClass.h"


Ghost::Ghost()
{
	_pos.SetRow(0);
	_pos.SetCol(0);
	_moves = 0;
	direction = Direction(rand() % 4);
	_startPos.SetRow(0);
	_startPos.SetCol(0);
}

Ghost::~Ghost()
{

}


void Ghost::SetPosition(const int row, const int col)
{
	_pos.SetRow(row);
	_pos.SetCol(col);
}


void Ghost::Print()const
{
	gotoxy(_pos.getRow(), _pos.getCol());
	if (Color)
	{
		cout << CYAN << Ghost_sign << RESET;
	}
	else
		cout << Ghost_sign;

}

void Ghost::UpdateMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board, Pacman & pacman)
{
	if (_moves == 20 || Obstacle(_pos.getRow(), _pos.getCol(), maxRow, maxCol, board, direction))
	{
		direction = SetMove(maxRow, maxCol, board);
		_moves = 0;
	}
	Movement(board);
	_moves++;
}

Direction Ghost::SmartMove(const int& maxRow, const int& maxCol, Pacman& pacman, vector<vector<GameBoard>>& board)
{
	//BFS
	const int maximumRow = 25, maximumCol = 80;
	bool visited[maximumRow][maximumCol];
	Qitem ghost(_pos.getRow(), _pos.getCol(), Direction::Stay);
	int i, j;
	for (i = 0 ; i < maxRow ; i++)
		for(j = 0 ; j < maxCol ; j++)
		{
			if (board[i][j].getSignpiece() == WALL)
				visited[i][j] = true;
			else
				visited[i][j] = false;
		}
	queue<Qitem> q;
	q.push(ghost);
	visited[ghost._row][ghost._col] = true;
	bool IsFirst = true;
	int sum = 0;
	Qitem p = q.front();
	while (!q.empty())
	{
		p = q.front();
		q.pop();

		// Destination found;
		if (pacman.getRow() == p._row)
			if(pacman.getCol() == p._col)
			return p._direction;

		// moving up
		if ((p._row - 1 >= 0) && (visited[p._row - 1][p._col] == false))
		{
			if (IsFirst == true)
			{
				q.push(Qitem(p._row - 1, p._col, Direction::Up)); //assigning up
			}
			else
			{
				q.push(Qitem(p._row - 1, p._col, p._direction));
			}
			visited[p._row - 1][p._col] = true;
		}

		// moving down
		if ((p._row + 1 < maxRow) && (visited[p._row + 1][p._col] == false))
		{
			if (IsFirst == true)
			{
				q.push(Qitem(p._row + 1, p._col, Direction::Down)); //assigning down
			}
			else
			{
				q.push(Qitem(p._row + 1, p._col, p._direction));
			}
			visited[p._row + 1][p._col] = true;
		}

		// moving left
		if ((p._col - 1 >= 0) && (visited[p._row][p._col - 1] == false))
		{
			if (IsFirst == true)
			{
				q.push(Qitem(p._row, p._col - 1, Direction::Left)); //assigning left
				
			}
			else
			{
				q.push(Qitem(p._row, p._col - 1, p._direction));
			}
			visited[p._row][p._col - 1] = true;
		}

		// moving right
		if ((p._col + 1 < maxCol) && (visited[p._row][p._col + 1] == false))
		{
			if (IsFirst == true)
			{
				q.push(Qitem(p._row, p._col + 1, Direction::Right)); //assigning right
				
			}
			else
			{
				q.push(Qitem(p._row, p._col + 1, p._direction));
			}
			visited[p._row][p._col + 1] = true;
		}
		if (IsFirst == true)
			IsFirst = false;

		sum++;
	}
	return Direction::Up;
}

