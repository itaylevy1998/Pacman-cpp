#pragma once
#include "GameBoard.h"
#include "GhostClass.h"
#include "Best_Ghost.h"
#include "Good_Ghost.h"
#include "PacmanClass.h"
#include "GameObject.h"
#include "Fruit.h"
#include <filesystem>
#include <string>
#include <fstream>


const int GameSpeed = 200;
const int GameOverWon = 3000;
extern bool Color;
using std::filesystem::directory_iterator;
const char filenamestart[] = "pacman_";
const char filenamefinish[] = ".screen";
const int SizeToCheck = 6;


class Game
{
private: 
	enum class CmdArg { Simple, Load, Save, Silent };
	vector<vector<GameBoard>> board;
	Pacman pacman;
	vector<Ghost*> ghosts;
	Position _legend;
	vector<string> GameFiles;
	Fruit fruit;
	CmdArg status;
	int _numBread;
	int maxRow;
	int maxCol;
public:
	Game();
	~Game();
	bool CheckImpact();
	void Start(int& argc, char** argv);
	void getCommandStatus(int& argc, char** argv);
	void PrintBoard() const;
	void Menu();
	void PrintMenu() const;
	void Instructions(char& user_input);
	void ChooseGhostLevel(int& GhostLevel);
	void GameRun(int& filedIndex);
	void getStepsResFileNames(string& steps, string& res, int& fileIndex);
	void GameRunLoadSilent();
	int ReadStepsFromFiles(int& fileIndex);
	void PacmanLoadCheck();
	void FruitLoad(string& line);
	void readFruitPos(string& line, int index, int fruitStatus);
	bool IsGamePaused(char &pause);
	bool IsMoveValid(const char& ch);
	void ConsequencesOfMove(bool& is_ghost_turn, ofstream& stepFile);
	void PacmanCheck();
	void CheckIfPacmanAteFood();
	void PrintScoreAndLives()const;
	void GhostInitialize();
	void PrintLifeLost() const; 
	void turnColor();
	void CheckGhostFruitImpact();
	void getGameFiles(bool& filesFound);
	void checkFileNameFormat();
	void getBoardInformation(int fileIndex, int & GhostLevel);
	void ClearGame();
	void RegularGame(int & GhostLevel);
	void SpecificFileCycle(int & GhostLevel);
	void ClearLevel();
	void DecideChar(const int& row, const int& col, const char& ch, bool& legend_appear, int & GhostLevel, bool& isPacman);
	void EndGameMessage() const;
	void WinGameMessage() const;
	void WaitMessage()const;
};
