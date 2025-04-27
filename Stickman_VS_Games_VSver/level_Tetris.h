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
	GameTetris();						 // 构造函数
	void initGame();					 // 初始化游戏矩阵
	void startGame();					 // 开始游戏
	void update(char key);				 // 根据输入更新游戏矩阵
	GameState state() const;			 // 获取游戏状态
	vector<vector<int>> getGrid() const; // 获取游戏矩阵
	int getScore() const;				 // 获取游戏得分
};

#endif