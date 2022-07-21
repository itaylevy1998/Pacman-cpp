#pragma once
#include <iostream>
const int SizeRow = 20;
const int SizeCol = 60;
const char FOOD = (char)248;
const char WALL = '#';
#include "GotoXY.h"
#include "Position.h"
extern bool Color;
const char YELLOW[] = "\033[33m";     /* Yellow */
const char BLUE[] = "\033[34m";      /* Blue */
const char RESET[] = "\033[0m";
const char GRAY[] = "\033[30;1m";
const char CYAN[] = "\033[36m";    /* Cyan */
const char FOODCOLOR[] = "\033[31m";
class GameBoard
{
private:
	//Position pos;
	char _sign;
public:
	GameBoard();
	~GameBoard();
	void setGamePiece(const char ch);
	void printPiece(const int& x, const int& y) const;
	//int getXpiece() const;
	//int getYpiece()const;
	char getSignpiece() const;
	
};





