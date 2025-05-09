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

	// ������״����
	static const int TETROMINO_COUNT = 7;
	static const int TETROMINO_SIZE = 4;
	char tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
		// I�η���
		{
			{' ', ' ', ' ', ' '},
			{'I', 'I', 'I', 'I'},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// J�η���
		{
			{'J', ' ', ' ', ' '},
			{'J', 'J', 'J', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// L�η���
		{
			{' ', ' ', 'L', ' '},
			{'L', 'L', 'L', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// O�η���
		{
			{' ', 'O', 'O', ' '},
			{' ', 'O', 'O', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// S�η���
		{
			{' ', 'S', 'S', ' '},
			{'S', 'S', ' ', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// T�η���
		{
			{' ', 'T', ' ', ' '},
			{'T', 'T', 'T', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}},
		// Z�η���
		{
			{'Z', 'Z', ' ', ' '},
			{' ', 'Z', 'Z', ' '},
			{' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' '}}};

	// ��ǰ����
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