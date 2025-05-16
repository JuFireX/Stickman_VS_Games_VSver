#include <windows.h>
#include <iostream>
#include "level_Pacman.h"

GamePacman::GamePacman() : rng(time(nullptr)) {}

void GamePacman::initGrid()
{
    // ��ͼ
    // ��ͼ
    int map[20][20] = {
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, FOOD, FOOD, FOOD, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, WALL, FOOD, WALL},
        {WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL},
        {WALL, FOOD, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, WALL},
        {WALL, FOOD, WALL, WALL, FOOD, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL, FOOD, WALL, WALL, WALL, WALL, WALL},
        {WALL, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, FOOD, WALL, WALL, WALL, WALL, WALL},
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL} };

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
    player.speed = 1;
    player.speed = 1;
    ghost[0].x = 18;
    ghost[0].y = 1;
    ghost[0].direction = Direction::LEFT;
    ghost[0].speed = 1;
    ghost[0].speed = 1;
    ghost[0].live = 1;
    ghost[1].x = 18;
    ghost[1].y = 16;
    ghost[1].direction = Direction::LEFT;
    ghost[1].speed = 1;
    ghost[1].live = 1;
    ghost[2].x = 1;
    ghost[2].y = 1;
    ghost[2].direction = Direction::RIGHT;
    ghost[2].speed = 1;
    ghost[2].form = 0;
    ghost[2].live = 1;
    // �ṹ�����帳ֵ
}
void GamePacman::initGame()
{
    gameOver = false;
    score = 0;
    initGrid();
    initMovers();
    updateGrid();
}
void GamePacman::updateGrid()
{
    // ���֮ǰ����Һ͹���λ��
    grid[player.old_y][player.old_x] = EMPTY;
    grid[ghost[0].old_y][ghost[0].old_x] = EMPTY;
    grid[ghost[1].old_y][ghost[1].old_x] = EMPTY;
    grid[ghost[2].old_y][ghost[2].old_x] = EMPTY;

    // �����µ�λ��
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
    player.old_x = player.x;
    player.old_y = player.y;
    switch (player.direction)
    {
    case Direction::RIGHT:
        if (grid[player.y][player.x + 1] != WALL)
        if (grid[player.y][player.x + 1] != WALL)
            player.x += player.speed;
        break;
    case Direction::UP:
        if (grid[player.y - 1][player.x] != WALL)
        if (grid[player.y - 1][player.x] != WALL)
            player.y -= player.speed;
        break;
    case Direction::LEFT:
        if (grid[player.y][player.x - 1] != WALL)
        if (grid[player.y][player.x - 1] != WALL)
            player.x -= player.speed;
        break;
    case Direction::DOWN:
        if (grid[player.y + 1][player.x] != WALL)
        if (grid[player.y + 1][player.x] != WALL)
            player.y += player.speed;
        break;
    }
    updateGrid();
}

void GamePacman::update(char key)
{
    if (processInput(key))
        movePlayer();
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
//���޸�
int GamePacman::getScore() const
{
    return 0;
}

GameState GamePacman::state() const
{
    return gameOver ? GameState::GameOver : GameState::Running;
}
// Test methods
void GamePacman::display(const vector<vector<int>> &grid, int size) const
{

    system("cls");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (grid[i][j] == WALL)
                cout << "  "; // �ո�
            else if (grid[i][j] == FOOD)
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
}

void GamePacman::startGame()
{
    initGame();
    display(getGrid(), 20);

    while (!gameOver)
    {
        if (_kbhit())
        {
            char input = _getch();
            if (input == 'q')
                break;
            update(input);
            display(getGrid(), 20);
        }
        // �Ը���
        else
        {
            update(' ');
            display(getGrid(), 20);
        }
        Sleep(200);
    }
}
//����Ϊ��Ⱦ����
void GamePacman::load()  
{  
   // �޸�����ȷ��·���Ͳ�����ȷ  
   loadimage(&player_img[0], _T("../PictureResource/GamePacman/RIGHT.png"), img_size, img_size, true);  
   loadimage(&player_img[1], _T("../PictureResource/GamePacman/LEFT.png"), img_size, img_size, true);
   loadimage(&player_img[2], _T("../PictureResource/GamePacman/UP.png"), img_size, img_size, true);
   loadimage(&player_img[3], _T("../PictureResource/GamePacman/DOWN.png"), img_size, img_size, true);
   loadimage(&player_img[4], _T("../PictureResource/GamePacman/close.png"), img_size, img_size, true);
   loadimage(&ghost_img[0], _T("../PictureResource/GamePacman/3.png"), img_size, img_size, true);
   loadimage(&ghost_img[1], _T("../PictureResource/GamePacman/4.png"), img_size, img_size, true);
   loadimage(&ghost_img[2], _T("../PictureResource/GamePacman/5.png"), img_size, img_size, true);
   loadimage(&Wall, _T("../PictureResource/GamePacman/wall.png"), img_size, img_size, true);
   loadimage(&Food, _T("../PictureResource/GamePacman/food.png"), 20, 20, true);
   MapImg[WALL] = Wall;
   MapImg[FOOD] = Food;
   MapImg[GHOST1] = ghost_img[0];
   MapImg[GHOST2] = ghost_img[1];
   MapImg[GHOST3] = ghost_img[2];
}

vector<vector<position>> GamePacman::getMap() const // �ػ��ͼ
{
    vector<vector<int>> state = getGrid();
    vector<vector<position>> GameMap;
    int sizeY = 480 / 24;
    int sizeX = 720 / 36;
    for (int i = 0; i < 24; i++)
    {
        vector<position> row;
        for (int j = 0; j < 36; j++)
        {
            row.push_back({ 0, j * sizeX, i * sizeY });
        }
        GameMap.push_back(row);
    }
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (state[i][j] != EMPTY)
            {
                GameMap[2+i][8+j].val = state[i][j];
            }
        }
    }
    return GameMap;
}