#pragma once
#include "GameObject.h"
#include "PacmanClass.h"
#include <queue>

using namespace std;
const char Ghost_sign = '$';
extern bool Color;

class Qitem
{
public:
	int _row;
	int _col;
	Direction _direction;
	Qitem(const int & row,const int& col, Direction dir) 
	{
		_row = row;
		_col = col;
		_direction = dir;
	}

};

class Ghost : public GameObject
{
public:
	Ghost();
	~Ghost();

	void SetPosition(const int row, const int col);

	void Print()const;
	virtual void UpdateMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board, Pacman& pacman);
	Direction SmartMove(const int& maxRow, const int& maxCol,Pacman &pacman, vector<vector<GameBoard>>& board);

	/*
protected:
	int move_counter;
	*/
};

