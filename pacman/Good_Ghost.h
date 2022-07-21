#pragma once
#include "GhostClass.h"
class Good_Ghost : public Ghost
{
private:
	bool smart;
	int randMove;

public:
	Good_Ghost();
	virtual void UpdateMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board , Pacman & pacman);
	int RandomizeMove();
};

