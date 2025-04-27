#ifndef LEVEL_2048_H
#define LEVEL_2048_H

#include <conio.h>
#include <ctime>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
#include <graphics.h>
#include <map>
#include "engine.h"

using namespace std;

class Game2048 : public Game
{
private:
	static const int GRID_SIZE = 4;
	int grid[GRID_SIZE][GRID_SIZE] = {0};
	bool gameOver = false;
	int score = 0;
	mt19937 rng;

	struct Position
	{
		int row;
		int col;
	};

	bool canMove(Direction dir) const;
	bool canMoveHorizontal(bool left) const;
	bool canMoveVertical(bool up) const;
	void moveAndMerge(Direction dir);
	void generateNewTile();
	bool isGameOver() const;
	bool processInput(char key);

	IMAGE img_2048[12];
	int img_size = 60;

public:
	Game2048();		  // 构造函数
	void initGame();  // 初始化游戏矩阵
	void startGame(); // 开始游戏

	void update(char key);				 // 根据输入更新游戏矩阵
	GameState state() const;			 // 获取游戏状态
	vector<vector<int>> getGrid() const; // 获取游戏矩阵
	int getScore() const;				 // 获取游戏得分

	void load(); // 加载游戏素材
	map<int, IMAGE> MapImg;
	vector<vector<Engine::position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 4;
};

#endif // LEVEL_2048_H
