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

private:
	static const int GRID_WIDTH = 10;
	static const int GRID_HEIGHT = 24;
	int grid[GRID_HEIGHT][GRID_WIDTH] = {0};
	int score = 0;
	mt19937 rng;

	// ?????????
	static const enum {
		EMPTY,
		WALL,
		BRICK
	} MAP;

	// ??????????????????????§³
	static const int TETROMINO_COUNT = 7;
	static const int TETROMINO_SIZE = 4;
	int tetrominos[TETROMINO_COUNT][TETROMINO_SIZE][TETROMINO_SIZE] = {
		// I?????
		{
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, BRICK},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// J?????
		{
			{BRICK, EMPTY, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// L?????
		{
			{EMPTY, EMPTY, BRICK, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// O?????
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// S?????
		{
			{EMPTY, BRICK, BRICK, EMPTY},
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// T?????
		{
			{EMPTY, BRICK, EMPTY, EMPTY},
			{BRICK, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}},
		// Z?????
		{
			{BRICK, BRICK, EMPTY, EMPTY},
			{EMPTY, BRICK, BRICK, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY}}};

	// ??????????
	int currentTetromino;
	
	int currentShape[TETROMINO_SIZE][TETROMINO_SIZE];

	void initGrid();
	void generateNewTetromino();
	bool canMoveTo(int newX, int newY);
	void rotateTetromino();
	void mergeTetromino();
	void clearLines();
	void display(const vector<vector<int>> &grid, int size) const; // ??????????
	bool processInput(char key);								   // ????????

	
	int img_size = 20;
public:
	GameTetris();						 // ??????
	void initGame();					 // ????????
	void startGame();					 // ???????
	void update(char key);				 // ????????????????
	GameState state() const;			 // ????????
	vector<vector<int>> getGrid() const; // ??????????
	int getScore() const;	// ???????¡Â?

	int tetrominoX = 0, tetrominoY = 0; // ????????¦Ë??
	bool gameOver = false;
	void load(); // ¼ÓÔØÓÎÏ·ËØ²Ä
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 20;
	int GameFrame = 6;
	IMAGE img_Tetris[12];
};

#endif
// LEVEL_TETRIS_H