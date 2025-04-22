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

using namespace std;

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// 定义游戏状态枚举，以便在其他游戏中使用
enum class GameState
{
	Running,
	GameOver
};

class Game2048
{
private:
	static const int GRID_SIZE = 4;
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };
	mt19937_64 rng;
	int score = 0;
	bool gameOver = false;

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

public:
	Game2048();
	void initGame();
	void display() const;
	bool processInput(char key);
	void startGame();
	vector<vector<int>> getGameState() const;
	int getScore() const;
	bool isGameFinished() const;

	//Game2048();
	//void init(); // 初始化游戏矩阵
	//void update(char key); // 根据输入更新游戏矩阵
	//GameState state() const; // 获取游戏状态
	//vector<vector<int>> matrix() const; // 获取游戏矩阵
	//int getScore() const;
};

#endif // LEVEL_2048_H
