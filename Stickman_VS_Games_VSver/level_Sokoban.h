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