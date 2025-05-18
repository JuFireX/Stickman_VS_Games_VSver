#ifndef LEVEL_SOKOBAN_H
#define LEVEL_SOKOBAN_H

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

class GameSokoban : public Game
{
private:
    static const int GRID_SIZE = 10;
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    int playerX = 1, playerY = 1;
    int boxCount = 0;
    int targetCount = 0;
    int level = 1;
    bool gameWon = false;

    // 定义地图元素
    static const enum {
        EMPTY,
        WALL,
        PLAYER,
        BOX,
        TARGET,
        BOX_ON_TARGET
    } MAP;

    void initLevel();                                              // 初始化游戏矩阵
    void checkWinCondition();                                      // 检查游戏是否结束
    bool movePlayer(Direction dir);                                // 移动玩家
    void display(const vector<vector<int>> &grid, int size) const; // 显示游戏矩阵
    bool processInput(char key);                                   // 处理用户输入

    IMAGE img_Sokoban[12];
    int img_size = 40; // 加载关卡
public:
    GameSokoban();                       // 构造函数
    void initGame();                     // 初始化游戏矩阵
    void startGame();                    // 开始游戏
    void update(char key);               // 根据输入更新游戏矩阵
    GameState state() const;             // 获取游戏状态
    vector<vector<int>> getGrid() const; // 获取游戏矩阵
    int getScore() const;                // 获取游戏得分

    bool gameOver = false;
    map<int, IMAGE> MapImg;
    void load(); // 加载游戏素材
    vector<vector<position>> getMap() const;
    int GameHigh = 12;
    int GridSize = 40;
    int GameFrame = 10; // 游戏刷新率
};

#endif
// LEVEL_SOKOBAN_H