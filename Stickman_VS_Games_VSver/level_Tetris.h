#ifndef LEVEL_TETRIS_H
#define LEVEL_TETRIS_H

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

class GameTetris : public Game
{
private:
	static const int GRID_WIDTH = 10;
	static const int GRID_HEIGHT = 24;
	int grid[GRID_HEIGHT][GRID_WIDTH] = { 0 };
	int score = 0;
	mt19937 rng;

	// 地图元素
	static const enum {
		EMPTY,
		WALL,
		BRICK
	} MAP;

	// 定义
	static const int TETROMINO_COUNT = 7;
	static const int TETROMINO_SIZE = 4;
	int tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
		// I
		{
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, BRICK},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// J
		{
			{BRICK, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// L
		{
			{EMPTY, EMPTY, BRICK, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// O
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// S
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// T
		{
			{EMPTY, BRICK, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		},
		// Z
		{
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}
		}
	};

	//
	int currentTetromino;

	int currentShape[TETROMINO_SIZE][TETROMINO_SIZE];

	void initGrid();
	void generateNewTetromino();
	bool canMoveTo(int newX, int newY);
	void rotateTetromino();
	void mergeTetromino();
	void clearLines();
	void display(const vector<vector<int>>& grid, int size) const; // 显示游戏矩阵
	bool processInput(char key);								   // 处理用户输入

	int img_size = 20;

public:
	GameTetris();						 // 构造函数
	void initGame();                     // 初始化游戏矩阵
	void startGame();                    // 开始游戏
	void update(char key);               // 根据输入更新游戏矩阵
	GameState state() const;             // 获取游戏状态
	vector<vector<int>> getGrid() const; // 获取游戏矩阵
	int getScore() const;                // 获取游戏得分

	int tetrominoX = 0, tetrominoY = 0;
	bool gameOver = false;
	void load(); // 加载游戏素材
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 20;
	int GameFrame = 6;
	IMAGE img_Tetris[12];
};

#endif
// LEVEL_TETRIS_H