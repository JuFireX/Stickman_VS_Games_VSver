#include <windows.h>
#include <iostream>
#include "level_Tetris.h"

GameTetris::GameTetris() : rng(time(nullptr)) {}

// Private methods

void GameTetris::initGrid()
{
    // 初始化网格为空
    for (int i = 0; i < GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < GRID_WIDTH; ++j)
        {
            grid[i][j] = EMPTY;
        }
    }
}

void GameTetris::generateNewTetromino()
{
    // 随机选择一个方块
    uniform_int_distribution<int> dist(0, TETROMINO_COUNT - 1);
    currentTetromino = dist(rng);

    // 复制方块形状
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            currentShape[i][j] = tetrominos[currentTetromino][i][j];
        }
    }

    // 设置初始位置（顶部中间）
    tetrominoX = GRID_WIDTH / 2 - 2;
    tetrominoY = 0;

    // 检查是否可以放置新方块，如果不能则游戏结束
    if (!canMoveTo(tetrominoX, tetrominoY))
    {
        gameOver = true;
    }
}

bool GameTetris::canMoveTo(int newX, int newY)
{
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            if (currentShape[i][j] != EMPTY)
            {
                int x = newX + j;
                int y = newY + i;

                // 检查边界
                if (x < 0 || x >= GRID_WIDTH || y >= GRID_HEIGHT)
                    return false;

                // 检查碰撞
                if (y >= 0 && grid[y][x] != EMPTY)
                    return false;
            }
        }
    }
    return true;
}

void GameTetris::rotateTetromino()
{
    // 创建临时数组存储旋转后的形状
    char temp[TETROMINO_SIZE][TETROMINO_SIZE];

    // 旋转90度（顺时针）
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            temp[j][TETROMINO_SIZE - 1 - i] = currentShape[i][j];
        }
    }

    // 检查旋转后是否可行
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            currentShape[i][j] = temp[i][j];
        }
    }

    // 如果旋转后不可行，则恢复原状
    if (!canMoveTo(tetrominoX, tetrominoY))
    {
        // 逆向旋转回去
        for (int i = 0; i < TETROMINO_SIZE; ++i)
        {
            for (int j = 0; j < TETROMINO_SIZE; ++j)
            {
                temp[i][j] = currentShape[j][TETROMINO_SIZE - 1 - i];
            }
        }

        for (int i = 0; i < TETROMINO_SIZE; ++i)
        {
            for (int j = 0; j < TETROMINO_SIZE; ++j)
            {
                currentShape[i][j] = temp[i][j];
            }
        }
    }
}

void GameTetris::mergeTetromino()
{
    // 将当前方块合并到网格中
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            if (currentShape[i][j] != EMPTY)
            {
                int y = tetrominoY + i;
                int x = tetrominoX + j;
                if (y >= 0)
                    grid[y][x] = currentShape[i][j];
            }
        }
    }
}

void GameTetris::clearLines()
{
    int linesCleared = 0;

    for (int i = GRID_HEIGHT - 1; i >= 0; --i)
    {
        bool lineFull = true;

        // 检查当前行是否已满
        for (int j = 0; j < GRID_WIDTH; ++j)
        {
            if (grid[i][j] == EMPTY)
            {
                lineFull = false;
                break;
            }
        }

        if (lineFull)
        {
            linesCleared++;

            // 将上面的行向下移动
            for (int k = i; k > 0; --k)
            {
                for (int j = 0; j < GRID_WIDTH; ++j)
                {
                    grid[k][j] = grid[k - 1][j];
                }
            }

            // 清空顶部行
            for (int j = 0; j < GRID_WIDTH; ++j)
            {
                grid[0][j] = EMPTY;
            }

            // 由于行已下移，需要重新检查当前行
            i++;
        }
    }

    // 根据消除的行数计算得分
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 800; // Tetris!
        break;
    }
}

void GameTetris::display(const vector<vector<int>> &grid, int size) const
{
    system("cls");

    for (int i = 0; i < GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < GRID_WIDTH; ++j)
        {
            if (grid[i][j] == WALL)
                cout << "# ";
            else if (grid[i][j] == BRICK)
                cout << "* ";
            else
                cout << "  ";
        }
        cout << "\n";
    }

    cout << "WASD to move, Q to quit." << endl;
    if (gameOver)
    {
        cout << "\nGame Over!\n"
             << endl;
    }
}

// Public methods

void GameTetris::initGame()
{
    gameOver = false;
    score = 0;
    initGrid();
    generateNewTetromino();
}

void GameTetris::startGame()
{
    initGame();
    display(getGrid(), GRID_HEIGHT);

    while (!gameOver)
    {
        // 处理用户输入
        if (_kbhit())
        {
            char input = _getch();
            if (input == 'q')
                break;

            update(input);
            display(getGrid(), GRID_HEIGHT);
        }
        // 自更新
        else
        {
            update(' ');
            display(getGrid(), GRID_HEIGHT);
        }

        Sleep(200);
    }
}

bool GameTetris::processInput(char key)
{
    switch (key)
    {
    case 'a': // 左移
        if (canMoveTo(tetrominoX - 1, tetrominoY))
            tetrominoX--;
        break;
    case 'd': // 右移
        if (canMoveTo(tetrominoX + 1, tetrominoY))
            tetrominoX++;
        break;
    case 'w': // 旋转
        rotateTetromino();
        break;
    case 's': // 加速下落
        if (canMoveTo(tetrominoX, tetrominoY + 1))
            tetrominoY++;
        break;
    case ' ':
        break;
    default:
        return false;
    }

    return true;
}

void GameTetris::update(char key)
{
    if (processInput(key))
    {
        // 自动下落逻辑
        if (canMoveTo(tetrominoX, tetrominoY + 1))
        {
            tetrominoY++;
        }
        else
        {
            // 无法下落，固定方块
            mergeTetromino();
            clearLines();
            generateNewTetromino();
        }
    }
}

GameState GameTetris::state() const
{
    return gameOver ? GameState::GameOver : GameState::Running;
}

vector<vector<int>> GameTetris::getGrid() const
{
    vector<vector<int>> gridCopy(GRID_HEIGHT, vector<int>(GRID_WIDTH));
    for (int i = 0; i < GRID_HEIGHT; ++i)
    {
        for (int j = 0; j < GRID_WIDTH; ++j)
        {
            gridCopy[i][j] = grid[i][j];
        }
    }

    // 将当前方块添加到显示网格
    for (int i = 0; i < TETROMINO_SIZE; ++i)
    {
        for (int j = 0; j < TETROMINO_SIZE; ++j)
        {
            if (currentShape[i][j] != EMPTY)
            {
                int y = tetrominoY + i;
                int x = tetrominoX + j;
                if (y >= 0 && y < GRID_HEIGHT && x >= 0 && x < GRID_WIDTH)
                    gridCopy[y][x] = currentShape[i][j];
            }
        }
    }

    return gridCopy;
}

int GameTetris::getScore() const
{
    return score;
}