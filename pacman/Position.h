#pragma once
#include "GotoXY.h"
using namespace std;
extern bool Color;

class Position
{
public:
	Position();
	Position(const Position& pos);
	~Position();

	void SetRow(const int& x);
	void SetCol(const int& y);

	int getCol() const;
	int getRow() const;

private:
	int _row;
	int _col;
};

