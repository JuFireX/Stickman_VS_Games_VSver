#include <windows.h>
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
        grid[8][2] = TARGET;
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

    if (grid[playerY][playerX] == TARGET)
        grid[playerY][playerX] = PLAYER; // 玩家站在目标上
    else
        grid[playerY][playerX] = PLAYER;

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
    }
}

void GameSokoban::display() const
{
    system("cls");
    cout << "Sokoban推箱子 - 关卡 " << level << "\n";
    cout << "箱子数量: " << boxCount << ", 目标数量: " << targetCount << "\n\n";

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << "\n";
    }

    cout << "\n使用WASD键移动, ESC退出\n";
    if (gameWon)
        cout << "\n恭喜! 你完成了关卡!\n";
}

// Public methods

void GameSokoban::initGame()
{
    level = 1;
    gameOver = false;
    gameWon = false;
    initLevel();
}

// Test methods

void GameSokoban::startGame()
{
    initGame();
    display();

    while (!gameOver)
    {
        char input = _getch();
        if (input == 27) // ESC键
            break;

        Direction dir;
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

        if (validMove)
        {
            display();

            if (gameWon)
            {
                cout << "按任意键继续...";
                _getch();
                level++;
                gameWon = false;
                initLevel();
                display();
            }
        }
    }
}