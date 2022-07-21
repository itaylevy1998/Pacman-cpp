#pragma once
#include "GhostClass.h"
class Best_Ghost :
    public Ghost
{
    virtual void UpdateMove(const int& maxRow, const int& maxCol, vector<vector<GameBoard>>& board, Pacman& pacman);
};

