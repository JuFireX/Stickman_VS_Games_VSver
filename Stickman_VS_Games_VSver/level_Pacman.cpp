#include <windows.h>
#include <iostream>
#include "level_Pacman.h"
GamePacman::GamePacman() : rng(time(nullptr))
{
}
void GamePacman::initGrid()
{
    int map[20][20] = {
            {WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL},
            {WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, PELLET, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL},
            {WALLLL, PELLET, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL},
            {WALLLL, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, PELLET, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL},
            {WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL, WALLLL}
    };

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = map[i][j];
        }
    }
}
void GamePacman::initMovers()
{
    player.x = 1;
    player.y = 18;
    player.direction = Direction::RIGHT;
    player.speed = 3;
    ghost[0].x = 18;
    ghost[0].y = 1;
    ghost[0].direction = Direction::LEFT;
    ghost[0].speed = 2;
    ghost[0].live = 1;
    ghost[1].x = 18;
    ghost[1].y = 16;
    ghost[1].direction = Direction::LEFT;
    ghost[1].speed = 2;
    ghost[1].live = 1;
    ghost[2].x = 1;
    ghost[2].y = 1;
    ghost[2].direction = Direction::RIGHT;
    ghost[2].speed = 1;
    ghost[2].form = 0;
    ghost[2].live = 1;
    //结构体整体赋值
}void GamePacman::updateGrid() {
    // 清除之前的玩家和鬼魂位置
    grid[player.y][player.x] = EMPTYY;
    grid[ghost[0].y][ghost[0].x] = EMPTYY;
    grid[ghost[1].y][ghost[1].x] = EMPTYY;
    grid[ghost[2].y][ghost[2].x] = EMPTYY;

    // 更新新的位置
    grid[player.y][player.x] = PLAYER;
    grid[ghost[0].y][ghost[0].x] = GHOST1;
    grid[ghost[1].y][ghost[1].x] = GHOST2;
    grid[ghost[2].y][ghost[2].x] = GHOST3;
}
bool GamePacman::processInput(char key)
{
    Direction newDir = player.direction;

    switch (key)
    {
    case 'a':
        newDir = Direction::LEFT;
        break;
    case 'd':
        newDir = Direction::RIGHT;
        break;
    case 'w':
        newDir = Direction::UP;
        break;
    case 's':
        newDir = Direction::DOWN;
        break;
    case ' ':
        break;
    default:
        return false;
    }
    player.direction = newDir;
    return true;
}
void GamePacman::movePlayer()
{
    switch (player.direction)
    {
    case Direction::RIGHT:
        if (grid[player.y][player.x + 1] != WALLLL)
            player.x += player.speed;
        break;
    case Direction::UP:
        if (grid[player.y - 1][player.x] != WALLLL)
            player.y -= player.speed;
        break;
    case Direction::LEFT:
        if (grid[player.y][player.x - 1] != WALLLL)
            player.x -= player.speed;
        break;
    case Direction::DOWN:
        if (grid[player.y + 1][player.x] != WALLLL)
            player.y += player.speed;
        break;
    }
    updateGrid();

}
//main
void GamePacman::initGame()
{
    gameOver = false;
    score = 0;
    initGrid();
    initMovers();
    updateGrid();
}


void GamePacman::update(char key)
{
    if (processInput(key))
        movePlayer();
}
int GamePacman::getScore() const
{
    return 0;
}
GameState GamePacman::state() const
{
    return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> GamePacman::getGrid() const
{
    vector<vector<int>> gridCopy(GRID_SIZE, vector<int>(GRID_SIZE));
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            gridCopy[i][j] = grid[i][j];
        }
    }
    return gridCopy;
}
// Test methods
void GamePacman::display(const vector<vector<int>>& grid, int size) const
{

    //    system("cls");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (grid[i][j] == WALLLL)
                cout << "# ";
            else if (grid[i][j] == PELLET)
                cout << "* ";
            else if (grid[i][j] == PLAYER)
                cout << "@ ";
            else if (grid[i][j] == GHOST1)
                cout << "1 ";
            else if (grid[i][j] == GHOST2)
                cout << "2 ";
            else if (grid[i][j] == GHOST3)
                cout << "3 ";
            else
                cout << "  ";
        }
        cout << endl;
    }


    cout << "\n使用WASD键移动, ESC退出\n";

}

void GamePacman::startGame() {
    initGame();
    display(getGrid(), 20);

    while (!gameOver) {
        if (_kbhit()) {
            char input = _getch();
            if (input == 'q')
                break;
            update(input);
            display(getGrid(), 20);
        }
        // 自更新
        else {
            update(' ');
            display(getGrid(), 20);
        }
        Sleep(200);
    }
}