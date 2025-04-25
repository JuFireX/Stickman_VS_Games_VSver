#ifndef LEVEL_SNAKE_H
#define LEVEL_SNAKE_H

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

class GameSnake : public Game
{

private:
    static const int GRID_SIZE = 20;
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };
    vector<pair<int, int>> snake;           // 蛇身体的坐标
    pair<int, int> food;                    // 食物的坐标
    Direction direction = Direction::RIGHT;
    bool gameOver = false;
    int score = 0;
    mt19937 rng;

    // 定义地图元素
    static const enum {
        EMPTY,
        SNAKE_HEAD,
        SNAKE_BODY,
        FOOD,
        WALL
    } MAP;

    void initGrid();
    void initSnake();
    void generateFood();
    void updateGrid();
    bool moveSnake();
    bool processInput(char key);

public:
    GameSnake();                         // 构造函数
    void initGame();                     // 初始化游戏
    void startGame();                    // 启动游戏
    void update(char key);               // 根据输入更新游戏状态
    GameState state() const;             // 获取游戏状态
    vector<vector<int>> getGrid() const; // 获取游戏网格
    int getScore() const;                // 获取游戏得分
};

#endif // LEVEL_SNAKE_H