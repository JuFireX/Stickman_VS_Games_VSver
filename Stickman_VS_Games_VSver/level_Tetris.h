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

enum class Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class GameState
{
    Running,
    GameOver
};

class GameTetris : public Game
{
};

#endif