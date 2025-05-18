#ifndef LEVEL_SNAKE_H
#define LEVEL_SNAKE_H

#include "engine.h"
#include <algorithm>
#include <conio.h>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

class GameSnake : public Game
{

private:
	static const int GRID_SIZE = 20;
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };
	vector<pair<int, int>> snake; // �����������
	pair<int, int> food;          // ʳ�������
	Direction direction = Direction::RIGHT;
	int score = 0;
	mt19937 rng;

	// �����ͼԪ��
	static const enum {
		EMPTY,
		WALL,
		SNAKE_HEAD,
		SNAKE_BODY,
		FOOD
	} MAP;

	void initGrid();
	void initSnake();
	void generateFood();
	bool moveSnake();
	void display(const vector<vector<int>>& grid, int size) const; // ��ʾ��Ϸ����
	bool processInput(char key);
	void updateGrid(); // ������Ϸ����

	IMAGE img_snake[4];
	int img_size = 20;

public:
	GameSnake();                         // ���캯��
	void initGame();                     // ��ʼ����Ϸ
	void startGame();                    // ������Ϸ
	void update(char key);               // �������������Ϸ״̬
	GameState state() const;             // ��ȡ��Ϸ״̬
	vector<vector<int>> getGrid() const; // ��ȡ��Ϸ����
	int getScore() const;                // ��ȡ��Ϸ�÷�

	bool gameOver = false;
	void load(); // ������Ϸ�ز�
	map<int, IMAGE> MapImg;
	vector<vector<position>> getMap() const;
	int GameHigh = 24;
	int GridSize = 20;
	int GameFrame = 4;
};

#endif
// LEVEL_SNAKE_H