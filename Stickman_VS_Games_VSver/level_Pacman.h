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
    IMAGE ghost_img[3];
    static const int GRID_SIZE = 20;
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    vector<pair<int, int>> snake;
    pair<int, int> food;
    Direction direction = Direction::RIGHT;
    int score = 0;
    mt19937 rng;

    void initMovers();
    void initGrid();
    void movePlayer();
    bool processInput(char key);
    void display(const vector<vector<int>> &grid, int size) const;
    void updateGrid(); // ������Ϸ����
    IMAGE Wall;
	IMAGE Food;
public:
    GamePacman();                        // ���캯��
    void initGame();                     // ��ʼ����Ϸ����
    void startGame();                    // ��ʼ��Ϸ
    void update(char key);               // �������������Ϸ����
    GameState state() const;             // ��ȡ��Ϸ״̬
    vector<vector<int>> getGrid() const; // ��ȡ��Ϸ����
    int getScore() const;                // ��ȡ��Ϸ�÷�

    bool gameOver = false;
    void load() override; // ������Ϸ�ز�
    map<int, IMAGE> MapImg;
    vector<vector<position>> getMap() const override;
    int GameHigh = 24;
    int GridSize = 4;
    int GameFrame = 6; // ��Ϸˢ����
    int img_size = 20;
    IMAGE player_img[5];
};

#endif
// level_Pacman.h
// level_Pacman.h