#include "Game.h"


Game::Game()
{
	_numBread = 0;
}

Game::~Game()
{
}

bool Game::CheckWall(const int& x,const int& y, GameBoard board[][SizeCol])
{
	if (board[x][y].getSignpiece() == WALL)
		return true;
	return false;
}

bool Game::CheckTunnel(const int& row, const int& col, GameBoard board[][SizeCol])
{
	if (col == 29)
	{
		if (row == 0 || row == 19)
			return true;
	}
	else if (row == 10)
		if (col == 0 || col == 59)
			return true;
	return false;
}

void Game::CheckImpact(Pacman& pacman, Ghost* ghosts, GameBoard board[][SizeCol])
{
	int i;
	for (i = 0; i < 2; i++)
	{
		if (pacman.getPacmanRow() == ghosts[i].getGhostRow())
			if (pacman.getPacmanCol() == ghosts[i].getGhostCol())
			{
				pacman.setPacmanLives();
				PrintLifeLost(pacman);
				GhostInitialize(ghosts);
				pacman.ResetPos();
				if (pacman.getPacmanLives() == 0)
					return;
				PrintBoard(board, pacman, ghosts);
				return;
			}
	}
	return;
}


void Game::GameCycle()
{
	Ghost ghosts[2]; 
	GhostInitialize(ghosts);
	Pacman pac;
	GameBoard board[SizeRow][SizeCol]; 
	InitBoard(board);
	PrintBoard(board, pac, ghosts);
	GameRun(pac, ghosts, board);


	
}

void Game::InitBoard(GameBoard board[][SizeCol])
{
	ifstream File;
	File.open("pacmanboard.txt");
	if (!File)
	{
		cout << "Error opening file!";
		exit(1);
	}
	int row, col;
	char sign;
	for (row = 0; row < SizeRow; row++)
		for (col = 0; col <= SizeCol; col++)
		{
			sign = File.get();
			if (sign != '\n')
			{
				if (!(row == StartRow && col == StartCol))
				{
					if (sign == '*')
					{
						_numBread++;
						sign = FOOD;
					}
				}
				else
					sign = ' ';
				board[row][col].setGamePiece(sign);
			}
		}
	File.close();
}

void Game::PrintBoard(GameBoard board[][SizeCol], Pacman& pacman, Ghost* ghosts) const
{
	int row, col;
	for(row=0; row <SizeRow; row++)
		for (col = 0; col < SizeCol; col++)
			board[row][col].printPiece(row,col);
	for (auto i = 0; i < 2; i++)
		ghosts[i].Print();
	pacman.printPacman();
	PrintScoreAndLives(pacman);
	
}

void Game::Menu()
{
	char user_input;
	PrintMenu();
	Color = false;
	do
	{
		user_input = _getch();
		switch (user_input)
		{
		case '1': GameCycle();
			break;
		case '7': turnColor();
			break;
		case '8': 
			Instructions(user_input);
			break;
		case '9': clrscr();
			cout << "Good Bye" << endl;
			return;
		default: clrscr();
			cout << "Incorrect input";
			Sleep(1400);
			break;
		}
		PrintMenu();	
	} while (true);

}

void Game::PrintMenu() const
{
	clrscr();
	cout << "Welcome To Pacman" << endl;
	cout << "(1) Start a new game" << endl;
	cout << "(7) Turn on/off colors" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}


void Game::Instructions(char& user_input)
{
	clrscr();
	cout << "Welcome To Pacman" << endl;
	cout << "Youre the pacman (@ in the game), your goal is to eat all the breadcumbs on the board" << endl;
	cout << "while avoiding the ghosts ($ in the game)." << endl;
	cout << "As pacman you start with 3 lives." << endl;
	cout << "If you get in contact with a ghost you will lose a life. if you lose 3 lives you also lose the game." << endl;
	cout << "When you lose a life the game will restart and you will be back to your intial position." << endl;
	cout << "But your score will be saved as will your breadcrumbs eating progress." << endl;
	cout << endl;
	cout << "Keys:" << endl;
	cout << "Move Left: A" << endl;
	cout << "Move Right: D" << endl;
	cout << "Move Up: W" << endl;
	cout << "Move Down: X" << endl;
	cout << "Stay: S" << endl;
	cout << "Pause: ESC" << endl;
	cout << endl;
	cout << "To return to the menu press ESC.";
	do
	{
		user_input = _getch();
	} while (user_input != 27);
}

void Game::GameRun(Pacman& pacman, Ghost* ghosts, GameBoard board[][SizeCol])
{
	char flush;
	char tmp_move = 0;
	bool is_ghost_turn = false;
	while (pacman.getPacmanLives() != 0 && _numBread != 0)//or pacman earned max points
	{
		if (IsGamePaused(tmp_move) == true) //waits until user select ESC again to continue game.
		{
			clrscr();
			PrintBoard(board, pacman, ghosts);
		}
		if (_kbhit()) //if the user pressed any key
		{
			tmp_move = getKey(); //get char entered by user.
			if (IsMoveValid(tmp_move) == true) //check if its a vaild move for pacman.
			{
				if (tmp_move == PAUSE)
					continue;
				else
					pacman.setPacmanDirection(tmp_move);
			}
		}
		
		ConsequencesOfMove(pacman, ghosts, board, is_ghost_turn);
		if (pacman.getPacmanLives() != 0)
			PrintScoreAndLives(pacman);
		Sleep(GameSpeed);
	}
	clrscr();
	gotoxy(10, 20);
	if (pacman.getPacmanLives() == 0)
		cout << "Game Over!";
	else
		cout << "Congratulations, you won!!";
	Sleep(GameOverWon);
	clrscr();
	cout << "Press any key to return to the menu";
	while (!_kbhit());
	flush = _getch();
	clrscr();
}

bool Game::IsGamePaused(char& pause)
{
	if (pause == PAUSE)
	{
		clrscr();
		gotoxy(0, 0);
		cout << "Game is paused. please press ESC to continue.";
		char tmp;
		while (pause == PAUSE)
		{
			if (_kbhit())
			{
				tmp = getKey();
				if (tmp == PAUSE)
					pause = 0;
			}
			Sleep(GameSpeed*2);
		}
		return true;
	}
	return false;
}

bool Game::IsMoveValid(const char& ch)
{
	if (ch == STAY || ch == (STAYS))
		return true;
	else if (ch == LEFT || ch == (LEFTA))
		return true;
	else if (ch == RIGHT || ch == (RIGHTD))
		return true;
	else if (ch == UP || ch == (UPW))
		return true;
	else if (ch == DOWN || ch == (DOWNX))
		return true;
	else if (ch == PAUSE)
		return true;
	else
		return false;
	
}

/*this function checks if pacman ate, hit a ghost, or got into a tunnel*/
void Game::ConsequencesOfMove(Pacman& pacman, Ghost* ghosts, GameBoard board[][SizeCol], bool& is_ghost_turn)
{
	int pacRow = pacman.getPacmanRow(), pacCol = pacman.getPacmanCol();
	board[pacRow][pacCol].printPiece(pacRow, pacCol);
	PacmanCheck(pacman, board);
	CheckImpact(pacman, ghosts, board);
	if (pacman.getPacmanLives() == 0)
		return;
	if (is_ghost_turn == true)// makes sure that ghosts move once in two pacman moves.
	{
		ghosts[0].UpdateMove(board); // updates the ghost's movements (if needed it changed direction)
		ghosts[1].UpdateMove(board);
		is_ghost_turn = false;
	}
	else
		is_ghost_turn = true;
	ghosts[0].Print();
	ghosts[1].Print();
	CheckImpact(pacman, ghosts, board);
	
}

void Game::PacmanCheck(Pacman& pacman, GameBoard board[][SizeCol])
{
	if (pacman.CheckIfPacmanHitWall(board) == true)
	{
		pacman.setPacmanDirection(STAY);
	}
	pacman.setPacmanPosition();
	//CheckIfPacmanAteFood(pacman, board);
	CheckTunnel(pacman, board);
	pacman.printPacman();
	CheckIfPacmanAteFood(pacman, board);
}

void Game::CheckIfPacmanAteFood(Pacman& pacman, GameBoard board[][SizeCol])
{
	if (board[pacman.getPacmanRow()][pacman.getPacmanCol()].getSignpiece() == FOOD)
	{
		pacman.setPacmanScore();
		_numBread--;
		board[pacman.getPacmanRow()][pacman.getPacmanCol()].setGamePiece(' ');
	}
}

void Game::PrintScoreAndLives(Pacman& pacman) const
{
	gotoxy(21, 0);
	cout << "Your score: " << pacman.getPacmanScore();
	gotoxy(21, 30);
	cout << "Remaining lives: " << pacman.getPacmanLives();
}


void Game::GhostInitialize(Ghost* ghosts)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		ghosts[i].SetPosition(StartGhostRow + i * 10, StartGhostCol);
	}
}

void Game::PrintLifeLost(Pacman& pacman)
{
	clrscr();
	
	if (pacman.getPacmanLives() > 0)
	{
		gotoxy(10, 30);
		cout << "The Pacman was eaten by a ghost." << endl;
		gotoxy(11, 30);
		cout << "You have " << pacman.getPacmanLives() << " lives reamining";
		Sleep(GameSpeed * 8);
	}
	clrscr();
}

void Game::CheckTunnel(Pacman& pacman, GameBoard[][SizeCol])
{
	int pacRow = pacman.getPacmanRow(), pacCol = pacman.getPacmanCol();
	if (pacRow == 10)
	{
		if (pacCol == 0)
		{
			pacman.setPacmanIfTunnel(pacRow, 58);
			return;
		}
		if (pacCol == 59)
		{
			pacman.setPacmanIfTunnel(pacRow, 1);
			return;
		}
	}
	if (pacCol == 29)
	{
		if (pacRow == 0)
		{
			pacman.setPacmanIfTunnel(18, pacCol);
			return;
		}
		if (pacRow == 19)
		{
			pacman.setPacmanIfTunnel(1, pacCol);
			return;
		}
	}
	return;
}

void Game::turnColor()
{
	clrscr();
	gotoxy(0, 0);
	if (!Color)
		cout << "Colors are turned On";
	else
		cout << "Colors are turend Off";
	Color = !Color;
	Sleep(GameSpeed * 2);
	clrscr();
}
