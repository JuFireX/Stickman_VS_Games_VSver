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
#include <map>
#include "engine.h"

using namespace std;

class Game2048 : public Game
{
private:
	static const int GRID_SIZE = 4;
	int grid[GRID_SIZE][GRID_SIZE] = {0};

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
	void display(const vector<vector<int>> &grid, int size) const; // ��ʾ��Ϸ����
	bool processInput(char key);

	IMAGE img_2048[12];
	int img_size = 60;

public:
	Game2048();									  // ���캯��
	void initGame() override;					  // ��ʼ����Ϸ����
	void startGame() override;					  // ��ʼ��Ϸ
	void update(char key) override;				  // �������������Ϸ����
	GameState state() const override;			  // ��ȡ��Ϸ״̬
	vector<vector<int>> getGrid() const override; // ��ȡ��Ϸ����
	int getScore() const override;				  // ��ȡ��Ϸ�÷�

	bool gameOver = false;
	void load() override; // ������Ϸ�ز�
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const override;
	int GameHigh = 24;
	int GridSize = 4;
	int GameFrame = 10; // ��Ϸˢ����
};

#endif // LEVEL_2048_H
