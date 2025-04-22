// engine.cpp

#include <memory>
#include<iostream>
#include "engine.h"
#include "level_2048.h"
#include "level_Mario.h"
#include "level_Pacman.h"
#include "level_Snake.h"
#include "level_Sokoban.h"
#include "level_Tetris.h"

using namespace std;

unique_ptr<Game> game;

extern "C" __declspec(dllexport) void startGame(Level level)
{
    switch (level)
    {
    case LEVEL_2048:
        game = make_unique<Game2048>();
        game->initGame();
        break;
    case LEVEL_MARIO:
        game = make_unique<GameMario>();
        game->initGame();
        break;
    case LEVEL_PACMAN:
        game = make_unique<GamePacman>();
        game->initGame();
        break;
    case LEVEL_SNAKE:
        game = make_unique<GameSnake>();
        game->initGame();
        break;
    case LEVEL_SOKOBAN:
        game = make_unique<GameSokoban>();
        game->initGame();
        break;
    case LEVEL_TETRIS:
        game = make_unique<GameTetris>();
        game->initGame();
        break;
    }
}

static void initWindow()
{
    // 初始化窗口代码
    cout << 0 << endl;
}

static void shutdownWindow()
{
    // 关闭窗口代码
    printf("%d", 0);
}

static char getKeyPress()
{
    // 获取按键输入的代码
    char key = _getch();
    return key;
}

static void renderGame()
{
    // 渲染游戏画面代码
    vector<vector<int>> grid = game->getGrid();
    system("cls");
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void Engine::init()
{
    // 初始化游戏窗口和图形资源
    // 假设我们已经有一个初始化窗口的函数 initWindow()
    initWindow();
}

void Engine::run()
{
    // 游戏主循环
    bool running = true;
    while (running)
    {
        // 处理输入事件
        char key = getKeyPress(); // 假设我们有一个获取按键输入的函数 getKeyPress()
        if (key == 'q')
        { // 如果按下 'q' 键，退出游戏
            running = false;
        }
        else if (game)
        {
            game->update(key);
        }

        // 更新游戏状态
        if (game && game->state() == GameState::GameOver)
        {
            running = false;
        }

        // 渲染游戏画面
        renderGame(); // 假设我们有一个渲染游戏画面的函数 renderGame()
    }
}

void Engine::shutdown()
{
    // 释放所有游戏资源
    game.reset();
    shutdownWindow(); // 假设我们有一个关闭窗口的函数 shutdownWindow()
}
