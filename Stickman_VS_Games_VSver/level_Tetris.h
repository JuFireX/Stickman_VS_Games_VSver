// level_Tetris.h
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
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include "engine.h"

using namespace std;

class GameTetris : public Game
{
private:
	static const int GRID_WIDTH = 10;
	static const int GRID_HEIGHT = 20;
	int grid[GRID_HEIGHT][GRID_WIDTH];
	int score;
	bool gameOver;
	mt19937 rng;

	// 定义地图元素类型
	static const enum {
		EMPTY,
		WALL,
		BRICK
	} MAP;

	// 定义不同的俄罗斯方块数量和大小
	static const int TETROMINO_COUNT = 7;
	static const int TETROMINO_SIZE = 4;
	int tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
		// I型方块
		{
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, BRICK},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// J型方块
		{
			{BRICK, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// L型方块
		{
			{EMPTY, EMPTY, BRICK, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// O型方块
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// S型方块
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// T型方块
		{
			{EMPTY, BRICK, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// Z型方块
		{
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}}};

	// 当前方块信息
	int currentTetromino;
	int tetrominoX;
	int tetrominoY;
	int currentShape[TETROMINO_SIZE][TETROMINO_SIZE];

	void initGrid();
	void generateNewTetromino();
	bool canMoveTo(int newX, int newY);
	void rotateTetromino();
	void mergeTetromino();
	void clearLines();
	void display() const;

public:
	GameTetris();
	void initGame();
	void startGame();
	void update(char key);
	GameState state() const;
	vector<vector<int>> getGrid() const;
	int getScore() const;
};

#endif
// LEVEL_TETRIS_H