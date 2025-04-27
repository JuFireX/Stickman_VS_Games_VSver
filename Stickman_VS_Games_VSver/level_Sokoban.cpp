#include <windows.h>
#include "level_Sokoban.h"

GameSokoban::GameSokoban() {}

// Private methods

void GameSokoban::initLevel()
{
    // ��ʼ������Ϊ��
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = EMPTY;
        }
    }

    // �����߽�ǽ
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        grid[0][i] = WALL;
        grid[GRID_SIZE - 1][i] = WALL;
        grid[i][0] = WALL;
        grid[i][GRID_SIZE - 1] = WALL;
    }

    // ���ݹؿ������ڲ�ǽ�����Ӻ�Ŀ��
    if (level == 1)
    {
        // ����һЩ�ڲ�ǽ
        grid[2][2] = WALL;
        grid[2][3] = WALL;
        grid[3][5] = WALL;
        grid[4][5] = WALL;
        grid[5][2] = WALL;
        grid[6][2] = WALL;
        grid[7][5] = WALL;
        grid[7][6] = WALL;

        // ��������
        grid[3][3] = BOX;
        grid[4][4] = BOX;
        grid[5][6] = BOX;

        // ����Ŀ��
        grid[8][2] = TARGET;
        grid[8][4] = TARGET;
        grid[8][7] = TARGET;

        // ������ҳ�ʼλ��
        playerX = 1;
        playerY = 1;
        grid[playerY][playerX] = PLAYER;
    }

    // �������Ӻ�Ŀ�������
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

    // ������λ��
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

    // �����λ���Ƿ���Ч
    if (grid[newY][newX] == WALL)
        return false;

    // �����λ�������ӣ�����Ƿ�����ƶ�
    if (grid[newY][newX] == BOX || grid[newY][newX] == BOX_ON_TARGET)
    {
        int boxNewX = newX + (newX - playerX);
        int boxNewY = newY + (newY - playerY);

        // ���������λ���Ƿ���Ч
        if (grid[boxNewY][boxNewX] == WALL || grid[boxNewY][boxNewX] == BOX || grid[boxNewY][boxNewX] == BOX_ON_TARGET)
            return false;

        // �ƶ�����
        if (grid[boxNewY][boxNewX] == TARGET)
            grid[boxNewY][boxNewX] = BOX_ON_TARGET;
        else
            grid[boxNewY][boxNewX] = BOX;

        // ����ԭ����λ��
        if (grid[newY][newX] == BOX_ON_TARGET)
            grid[newY][newX] = TARGET;
        else
            grid[newY][newX] = EMPTY;
    }

    // �ƶ����
    if (grid[playerY][playerX] == PLAYER)
        grid[playerY][playerX] = EMPTY;

    playerX = newX;
    playerY = newY;

    if (grid[playerY][playerX] == TARGET)
        grid[playerY][playerX] = PLAYER; // ���վ��Ŀ����
    else
        grid[playerY][playerX] = PLAYER;

    // ����Ƿ���ɹؿ�
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
    cout << "Sokoban������ - �ؿ� " << level << "\n";
    cout << "��������: " << boxCount << ", Ŀ������: " << targetCount << "\n\n";

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            cout << grid[i][j] << ' ';
        }
        cout << "\n";
    }

    cout << "\nʹ��WASD���ƶ�, ESC�˳�\n";
    if (gameWon)
        cout << "\n��ϲ! ������˹ؿ�!\n";
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
        if (input == 27) // ESC��
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
        case 'r': // ���ùؿ�
            initLevel();
            validMove = true;
            break;
        }

        if (validMove)
        {
            display();

            if (gameWon)
            {
                cout << "�����������...";
                _getch();
                level++;
                gameWon = false;
                initLevel();
                display();
            }
        }
    }
}