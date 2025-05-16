#ifndef LEVEL_PACMAN_H
#define LEVEL_PACMAN_H

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

class GamePacman : public Game
{
private:
    // �����ͼԪ��
    static const enum {
        EMPTY,
        WALL,
        PLAYER,
        GHOST1,
        GHOST2,
        GHOST3,
        FOOD
    } MAP;

    struct man
    {
        int x;
        int y;
        int old_x;
        int old_y;
        Direction direction;
        int speed;
        bool live;
        bool close;
    } player;

    struct ghost
    {
        int x;
        int y;
        int old_x;
        int old_y;
        Direction direction;
        int speed;
        int form;
        bool live;
    } ghost[3];

    static const int GRID_SIZE = 20;
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };
    vector<pair<int, int>> snake;
    pair<int, int> food;
    Direction direction = Direction::RIGHT;
    bool gameOver = false;
    int score = 0;
    mt19937 rng;

    void initMovers();
    void initGrid();
    void movePlayer();
    bool processInput(char key);
    void display(const vector<vector<int>>& grid, int size) const;
    void updateGrid(); // ������Ϸ����

public:
    GamePacman();                        // ���캯��
    void initGame();                     // ��ʼ����Ϸ����
    void startGame();                    // ��ʼ��Ϸ
    void update(char key);               // �������������Ϸ����
    GameState state() const;             // ��ȡ��Ϸ״̬
    vector<vector<int>> getGrid() const; // ��ȡ��Ϸ����
    int getScore() const;                // ��ȡ��Ϸ�÷�
};

#endif
// level_Pacman.h