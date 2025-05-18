#ifndef LEVEL_SNAKE_H
#define LEVEL_SNAKE_H

#include "engine.h"
#include <algorithm>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

class GameSnake : public Game
{

private:
	static const int GRID_SIZE = 20;
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };
	vector<pair<int, int>> snake; // 蛇身体的坐标
	pair<int, int> food;          // 食物的坐标
	Direction direction = Direction::RIGHT;
	int score = 0;
	mt19937 rng;

	// 定义地图元素
	static const enum {
		EMPTY,
		WALL,
		SNAKE_HEAD,
		SNAKE_BODY,
		FOOD
	} MAP;

	void initGrid();
	void initSnake();
	void generateFood();
	bool moveSnake();
	void display(const vector<vector<int>>& grid, int size) const; // 显示游戏矩阵
	bool processInput(char key);
	void updateGrid(); // 更新游戏网格

	IMAGE img_snake[4];
	int img_size = 20;

public:
	GameSnake();                         // 构造函数
	void initGame();                     // 初始化游戏
	void startGame();                    // 启动游戏
	void update(char key);               // 根据输入更新游戏状态
	GameState state() const;             // 获取游戏状态
	vector<vector<int>> getGrid() const; // 获取游戏网格
	int getScore() const;                // 获取游戏得分

	bool gameOver = false;
	void load(); // 加载游戏素材
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 20;
	int GameFrame = 4;
};

#endif
// LEVEL_SNAKE_H