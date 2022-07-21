#pragma once
#include "GameObject.h"

const char Pacman_sign = '@';
const char UP = 'w';
const char UPW = 'W';
const char DOWN= 'x';
const char DOWNX = 'X';
const char RIGHT = 'd';
const char RIGHTD = 'D';
const char LEFT = 'a';
const char LEFTA = 'A';
const char PAUSE = 27;
const char STAY = 's';
const char STAYS = 'S';
const int StartScore = 0;
const int StartLives = 3;
extern bool Color;

class Pacman : public GameObject
{
private:
	int _score;
	int _remaininglives;

public:
	Pacman(const int row = 0, const int col = 0, const int score = StartScore, const int Lives = StartLives, const Direction _direction = Direction::Stay);
	~Pacman();
	void setPacmanPosition();
	void setPacmanScore(int bonus = 1);
	void setPacmanLives(int minus = 1);
	void setPacmanDirection(const char& direction);
	void setPacmanIfTunnel(const int row, const int col);
	void resetPacmanScore(const int& StartScore);
	void resetPacmanLives(const int& StartLives);
	void printPacman() const; 
	int getPacmanScore() const;
	int getPacmanLives() const;
	void ResetPos();
	bool CheckIfPacmanHitWall(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board);
	virtual bool CheckTunnel(const int& maxRow,const int& maxCol, vector<vector<GameBoard>>& board);
};
