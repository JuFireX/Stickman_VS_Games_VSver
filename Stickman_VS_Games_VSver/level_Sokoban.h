#ifndef LEVEL_SOKOBAN_H
#define LEVEL_SOKOBAN_H

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

class GameSokoban : public Game
{
private:
    static const int GRID_SIZE = 10;
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    int playerX=1, playerY=1;
    int boxCount = 0;
    int targetCount = 0;
    int level = 1;
    bool gameOver = false;
    bool gameWon = false;

    // �����ͼԪ��
    static const enum {
        EMPTY,
        WALL,
        PLAYER,
        BOX,
        TARGET,
        BOX_ON_TARGET
    } MAP;


    void initLevel(); // ��ʼ����Ϸ����
    void checkWinCondition(); // �����Ϸ�Ƿ����
    bool movePlayer(Direction dir); // �ƶ����
    void display() const; // ��ʾ��Ϸ����

public:
	GameSokoban();							 // ���캯��
	void initGame();					 // ��ʼ����Ϸ����
	void startGame();					 // ��ʼ��Ϸ
	void update(char key);				 // �������������Ϸ����
	GameState state() const;			 // ��ȡ��Ϸ״̬
	vector<vector<int>> getGrid() const; // ��ȡ��Ϸ����
	int getScore() const;				 // ��ȡ��Ϸ�÷�
};

#endif // LEVEL_SOKOBAN_H