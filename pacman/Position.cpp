#include "Position.h"

Position::Position()
{
	_row = 0;
	_col = 0;
}

Position::Position(const Position& pos)
{
	_row = pos._row;
	_col = pos._col;
}

Position::~Position()
{
}

void Position::SetRow(const int& row)
{
	_row = row;
}

void Position::SetCol(const int& col)
{
	_col = col;
}

int Position::getRow() const
{
	return _row;
}

int Position::getCol() const
{
	return _col;
}
