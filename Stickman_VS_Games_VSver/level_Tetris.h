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

	// ��ͼԪ��
	static const enum {
		EMPTY,
		WALL,
		BRICK
	} MAP;

	// ����
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
	void display(const vector<vector<int>>& grid, int size) const; // ��ʾ��Ϸ����
	bool processInput(char key);								   // �����û�����

	int img_size = 20;

public:
	GameTetris();						 // ���캯��
	void initGame();                     // ��ʼ����Ϸ����
	void startGame();                    // ��ʼ��Ϸ
	void update(char key);               // �������������Ϸ����
	GameState state() const;             // ��ȡ��Ϸ״̬
	vector<vector<int>> getGrid() const; // ��ȡ��Ϸ����
	int getScore() const;                // ��ȡ��Ϸ�÷�

	int tetrominoX = 0, tetrominoY = 0;
	bool gameOver = false;
	void load(); // ������Ϸ�ز�
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 20;
	int GameFrame = 6;
	IMAGE img_Tetris[12];
};

#endif
// LEVEL_TETRIS_H