#include <windows.h>
#include <iostream>
#include "level_Sokoban.h"

GameSokoban::GameSokoban() {}

// Private methods

void GameSokoban::initLevel()
{
    // 初始化网格为空
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = EMPTY;
        }
    }

    // 创建边界墙
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        grid[0][i] = WALL;
        grid[GRID_SIZE - 1][i] = WALL;
        grid[i][0] = WALL;
        grid[i][GRID_SIZE - 1] = WALL;
    }

    // 根据关卡设置内部墙、箱子和目标
    if (level == 1)
    {
        // 设置一些内部墙
        grid[2][2] = WALL;
        grid[2][3] = WALL;
        grid[3][5] = WALL;
        grid[4][5] = WALL;
        grid[5][2] = WALL;
        grid[6][2] = WALL;
        grid[7][5] = WALL;
        grid[7][6] = WALL;

        // 设置箱子
        grid[3][3] = BOX;
        grid[4][4] = BOX;
        grid[5][6] = BOX;

        // 设置目标
        grid[8][1] = TARGET;
        grid[8][4] = TARGET;
        grid[8][7] = TARGET;

        // 设置玩家初始位置
        playerX = 1;
        playerY = 1;
        grid[playerY][playerX] = PLAYER;
    }

    // 计算箱子和目标的数量
    boxCount = 0;
    targetCount = 0;
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == BOX)
                boxCount++;
            else if (grid[i][j] == TARGET)
                targetCount++;
        }
    }
}

bool GameSokoban::movePlayer(Direction dir)
{
    int newX = playerX;
    int newY = playerY;

    // 计算新位置
    switch (dir)
    {
    case Direction::LEFT:
        newX--;
        break;
    case Direction::RIGHT:
        newX++;
        break;
    case Direction::UP:
        newY--;
        break;
    case Direction::DOWN:
        newY++;
        break;
    }

    // 检查新位置是否有效
    if (grid[newY][newX] == WALL)
        return false;

    // 如果新位置是箱子，检查是否可以推动
    if (grid[newY][newX] == BOX || grid[newY][newX] == BOX_ON_TARGET)
    {
        int boxNewX = newX + (newX - playerX);
        int boxNewY = newY + (newY - playerY);

        // 检查箱子新位置是否有效
        if (grid[boxNewY][boxNewX] == WALL || grid[boxNewY][boxNewX] == BOX || grid[boxNewY][boxNewX] == BOX_ON_TARGET)
            return false;

        // 移动箱子
        if (grid[boxNewY][boxNewX] == TARGET)
            grid[boxNewY][boxNewX] = BOX_ON_TARGET;
        else
            grid[boxNewY][boxNewX] = BOX;

        // 更新原箱子位置
        if (grid[newY][newX] == BOX_ON_TARGET)
            grid[newY][newX] = TARGET;
        else
            grid[newY][newX] = EMPTY;
    }

    // 移动玩家
    if (grid[playerY][playerX] == PLAYER)
        grid[playerY][playerX] = EMPTY;

    playerX = newX;
    playerY = newY;
    bool needFreshTarget = false;

    if (grid[playerY][playerX] == TARGET)
    {
        grid[playerY][playerX] = PLAYER; // 玩家站在目标上
        needFreshTarget = true;
    }
    else
    {
        grid[playerY][playerX] = PLAYER;
        if (needFreshTarget)
        {
            for (int i = 0; i < GRID_SIZE; ++i) // 还原目标
            {
                for (int j = 0; j < GRID_SIZE; ++j)
                {
                    if (grid[i][j] == TARGET)
                        grid[i][j] = TARGET;
                    if (grid[i][j] != BOX_ON_TARGET)
                        grid[i][j] = BOX_ON_TARGET;
                }
            }
            needFreshTarget = false;
        }
    }

    // 检查是否完成关卡
    checkWinCondition();

    return true;
}

void GameSokoban::checkWinCondition()
{
    int boxesOnTarget = 0;
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == BOX_ON_TARGET)
                boxesOnTarget++;
        }
    }

    if (boxesOnTarget == targetCount && targetCount > 0)
    {
        gameWon = true;
        gameOver = true;
    }
}

bool GameSokoban::processInput(char input)
{
    bool validMove = false;

    switch (input)
    {
    case 'a':
        validMove = movePlayer(Direction::LEFT);
        break;
    case 'd':
        validMove = movePlayer(Direction::RIGHT);
        break;
    case 'w':
        validMove = movePlayer(Direction::UP);
        break;
    case 's':
        validMove = movePlayer(Direction::DOWN);
        break;
    case 'r': // 重置关卡
        initLevel();
        validMove = true;
        break;
    }
    return validMove;
}

// Public methods

void GameSokoban::initGame()
{
    level = 1;
    gameOver = false;
    gameWon = false;
    initLevel();
}

void GameSokoban::update(char key)
{
    processInput(key);
}
GameState GameSokoban::state() const
{
    return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> GameSokoban::getGrid() const
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

int GameSokoban::getScore() const
{
    return level;
}

// Test methods
void GameSokoban::display(const vector<vector<int>>& grid, int size) const
{
    system("cls");

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (grid[i][j] == EMPTY)
                cout << "  ";
            else if (grid[i][j] == WALL)
                cout << "# ";
            else if (grid[i][j] == PLAYER)
                cout << "@ ";
            else if (grid[i][j] == BOX)
                cout << "B ";
            else if (grid[i][j] == BOX_ON_TARGET)
                cout << "X ";
            else if (grid[i][j] == TARGET)
                cout << "T ";
            else
                cout << "  ";
        }
        cout << "\n";
    }
}

void GameSokoban::startGame()
{
    initGame();
    display(getGrid(), 10);

    while (!gameOver)
    {
        if (_kbhit())
        {
            char input = _getch();
            if (input == 'q')
                break;
            update(input);
            display(getGrid(), 10);
        }
        // 非自更新
    }
}
//目测要加三个函数（以下部分与主逻辑无关）

void GameSokoban::load()
{
    loadimage(&img_Sokoban[0], _T("./PictureResource/GameSokoban/wall.png"), img_size, img_size, true);
    loadimage(&img_Sokoban[1], _T("./PictureResource/GameSokoban/box.jpg"), img_size, img_size, true);
    loadimage(&img_Sokoban[2], _T("./PictureResource/GameSokoban/player.png"), img_size, img_size, true);
    loadimage(&img_Sokoban[3], _T("./PictureResource/GameSokoban/target.png"), img_size, img_size, true);
    loadimage(&img_Sokoban[4], _T("./PictureResource/GameSokoban/target_on_boa.png"), img_size, img_size, true);
    MapImg[WALL] = img_Sokoban[0];
    MapImg[BOX] = img_Sokoban[1];
    MapImg[PLAYER] = img_Sokoban[2];
    MapImg[TARGET] = img_Sokoban[3];
    MapImg[BOX_ON_TARGET] = img_Sokoban[4];
}

vector<vector<position>> GameSokoban::getMap() const // 重绘地图
{
    vector<vector<int>> state = getGrid();
    vector<vector<position>> GameMap;
    int sizeY = 480 / 12;
    int sizeX = 720 / 18;
    for (int i = 0; i < 12; i++)
    {
        vector<position> row;
        for (int j = 0; j < 18; j++)
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
                GameMap[1+i][4+j].val = state[i][j];
            }
        }
    }
    return GameMap;
}
