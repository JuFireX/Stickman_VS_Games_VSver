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
#include "engine.h"

using namespace std;

enum class Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class GameState
{
	Running,
	GameOver
};

class Game2048 : public Game
{
private:
	static const int GRID_SIZE = 4;
	int grid[GRID_SIZE][GRID_SIZE] = {0};
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
	Game2048();							// ���캯��
	void init();						// ��ʼ����Ϸ����
	void update(char key);				// �������������Ϸ����
	GameState state() const;			// ��ȡ��Ϸ״̬
	vector<vector<int>> matrix() const; // ��ȡ��Ϸ����
	int getScore() const;				// ��ȡ��Ϸ�÷�
};

#endif // LEVEL_2048_H
