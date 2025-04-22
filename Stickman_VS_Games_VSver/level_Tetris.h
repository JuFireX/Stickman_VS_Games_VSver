#ifndef LEVEL_TETRIS_H
#define LEVEL_TETRIS_H

#include <conio.h>
#include <ctime>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
#include "engine.h"

using namespace std;

class GameTetris : public Game
{
public:
    void initGame() override {}
    void update(char key) override {}
    GameState state() const override { return GameState::GameOver; }
    vector<vector<int>> getGrid() const override { return {}; }
    int getScore() const override { return 0; }
};

#endif