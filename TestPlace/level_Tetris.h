// level2.h
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
#include <windows.h>
#include "engine.h"

using namespace std;

class GameTetris : public Game
{
private:
	static const int GRID_WIDTH = 10;
	static const int GRID_HEIGHT = 20;
	char grid[GRID_HEIGHT][GRID_WIDTH];
	int score;
	bool gameOver;
	mt19937 rng;

	// 方块形状定义
	static const int TETROMINO_COUNT = 7;
	static const int TETROMINO_SIZE = 4;
	char tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
		// I形方块
		{
			{' ', ' ', ' ', ' '},
			{'I', 'I', 'I', 'I'},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// J形方块
		{
			{'J', ' ', ' ', ' '},
			{'J', 'J', 'J', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// L形方块
		{
			{' ', ' ', 'L', ' '},
			{'L', 'L', 'L', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// O形方块
		{
			{' ', 'O', 'O', ' '},
			{' ', 'O', 'O', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// S形方块
		{
			{' ', 'S', 'S', ' '},
			{'S', 'S', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// T形方块
		{
			{' ', 'T', ' ', ' '},
			{'T', 'T', 'T', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// Z形方块
		{
			{'Z', 'Z', ' ', ' '},
			{' ', 'Z', 'Z', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}}};

	// 当前方块
	int currentTetromino;
	int tetrominoX;
	int tetrominoY;
	char currentShape[TETROMINO_SIZE][TETROMINO_SIZE];

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
	vector<vector<char>> getGrid() const;
	int getScore() const;
};

#endif // LEVEL_TETRIS_H