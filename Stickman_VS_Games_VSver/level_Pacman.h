#ifndef LEVEL_PACMAN_H
#define LEVEL_PACMAN_H

#include "engine.h"
#include <algorithm>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class GamePacman : public Game
{
private:
	static const enum {
		EMPTY,
		WALL,
		PLAYER,
		GHOST1,
		GHOST2,
		GHOST3,
		FOOD
	} MAP;

	struct man
	{
		int x;
		int y;
		int old_x;
		int old_y;
		Direction direction;
		int speed;
		bool live;
		bool close;
	} player;

	struct ghost
	{
		int x;
		int y;
		int old_x;
		int old_y;
		Direction direction;
		int speed;
		int form;
		bool live;
	} ghost[3];

	static const int GRID_SIZE = 20;
	int food_grid[GRID_SIZE][GRID_SIZE] = { 0 };
	int run_grid[GRID_SIZE][GRID_SIZE] = { 0 };
	int run_grid_copy[GRID_SIZE][GRID_SIZE] = { 0 };
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };

	Direction direction = Direction::RIGHT;
	// bool gameOver = false;
	int score = 0;
	int target = 0;
	mt19937 rng;

	void initMovers();
	void initGrid();
	void movePlayer();
	void moveGhosts();
	void judgeScore();
	int ghostDirection(int ghostX, int ghostY, int playerX, int playerY, int* track_x, int* track_y);
	bool processInput(char key);
	void display(const vector<vector<int>>& grid, int size) const;
	void updateGrid(); // 更新游戏网格

	IMAGE ghost_img[3];
	IMAGE Wall;
	IMAGE Food;

public:
	GamePacman();                        // 构造函数
	void initGame();                     // 初始化游戏
	void startGame();                    // 启动游戏
	void update(char key);               // 根据输入更新游戏状态
	GameState state() const;             // 获取游戏状态
	vector<vector<int>> getGrid() const; // 获取游戏网格
	int getScore() const;                // 获取游戏得分

	bool gameOver = false;
	void load() override; // 加载游戏素材
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const override;
	int GameHigh = 24;
	int GridSize = 4;
	int GameFrame = 6; // 游戏帧数
	int img_size = 20;
	IMAGE player_img[5];
	int phase = 0;
	bool canChangeDirection = true;
};

#endif
// level_Pacman.h