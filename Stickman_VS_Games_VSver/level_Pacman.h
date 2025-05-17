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
    int food_grid[GRID_SIZE][GRID_SIZE] = { 0 };
    int run_grid[GRID_SIZE][GRID_SIZE] = { 0 };
    int grid[GRID_SIZE][GRID_SIZE] = { 0 };
    
    Direction direction = Direction::RIGHT;
    //bool gameOver = false;
    int score = 0;
    int target = 0;
    mt19937 rng;

    void initMovers();
    void initGrid();
    void movePlayer();
    void moveGhosts();
    int ghost1(int g_map_x, int g_map_y, int p_map_x, int p_map_y, int* g1_track_x, int* g1_track_y);
    int judgeScore();
    bool processInput(char key);
    void display(const vector<vector<int>>& grid, int size) const;
    void updateGrid(); // 更新游戏网格

    IMAGE ghost_img[3];
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
    int phase = 0;
};

#endif
// level_Pacman.h
// level_Pacman.h